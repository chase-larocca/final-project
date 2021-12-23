#include "utils/lodepng.h"
#include "utils/SourcePath.cpp.in"
#include "common.h"
#include "mapping.h"

#include <string>
#include <string>

using namespace std;


//lighting parameters
vec4 light_position(0.0, 0.0, 10.0, 1.0);
vec4 ambient(0.0, 0.0, 0.0, 1.0);

Mesh* mesh;

//OpenGL draw variables
GLuint buffer;
GLuint vao;
GLuint  ModelViewEarth, ModelViewLight, NormalMatrix, Projection;
bool wireframe;
GLuint program;

// Texture objects references
GLuint month_texture;
GLuint night_texture;
GLuint cloud_texture;
GLuint perlin_texture;

#ifdef _WIN32
static
unsigned int lodepng_decode_wfopen(std::vector<unsigned char>& out, unsigned& w, unsigned& h,
    const std::string& filename,
    LodePNGColorType colortype = LCT_RGBA, unsigned bitdepth = 8)
{
    std::wstring wcfn;
    if (u8names_towc(filename.c_str(), wcfn) != 0)
        return 78;
    FILE* fp = _wfopen(wcfn.c_str(), L"rb");
    if (fp == NULL) { return 78; }

    std::vector<unsigned char> buf;
    fseek(fp, 0L, SEEK_END);
    long const size = ftell(fp);
    if (size < 0) {
        fclose(fp);
        return 78;
    }

    fseek(fp, 0L, SEEK_SET);
    buf.resize(size);
    fread(buf.data(), 1, size, fp);
    fclose(fp);

    return lodepng::decode(out, w, h, buf, colortype, bitdepth);
}
#endif //_WIN32

void loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex) {

    std::vector<unsigned char> image;
    unsigned int width;
    unsigned int height;
    //decode
#ifdef _WIN32
    unsigned error = lodepng_decode_wfopen(image, width, height, lpszPathName, LCT_RGBA, 8);
#else
    unsigned error = lodepng::decode(image, width, height, lpszPathName, LCT_RGBA, 8);
#endif //_WIN32

    //if there's an error, display it
    if (error) {
        std::cout << "decoder error " << error;
        std::cout << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    /* the image "shall" be in RGBA_U8 format */

    std::cout << "Image loaded: " << width << " x " << height << std::endl;
    std::cout << image.size() << " pixels.\n";
    std::cout << "Image has " << image.size() / (width * height) << "color values per pixel.\n";

    GLint GL_format = GL_RGBA;

    glActiveTexture(GLtex);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_format, width, height, 0, GL_format, GL_UNSIGNED_BYTE, &image[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Put things away and free memory
    image.clear();
}


void Mapping::start() {

    std::string vshader = source_path + "/shaders/vshader.glsl";
    std::string fshader = source_path + "/shaders/fshader.glsl";

    GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
    GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    check_shader_compilation(vshader, vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    check_shader_compilation(fshader, fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    check_program_link(program);

    glUseProgram(program);

    glBindFragDataLocation(program, 0, "fragColor");

    //Per vertex attributes
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    GLuint vNormal = glGetAttribLocation(program, "vNormal");
    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");

    //Retrieve and set uniform variables
    glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
    glUniform4fv(glGetUniformLocation(program, "ambient"), 1, ambient);

    //Matrix uniform variable locations
    ModelViewEarth = glGetUniformLocation(program, "ModelViewEarth");
    ModelViewLight = glGetUniformLocation(program, "ModelViewLight");
    NormalMatrix = glGetUniformLocation(program, "NormalMatrix");
    Projection = glGetUniformLocation(program, "Projection");

    //===== Send data to GPU ======
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &buffer);

    mesh = new Mesh();
    mesh->makeSphere(32);

    std::string arena_img = source_path + "/images/arena.png";
    //world.200405.3.
    loadFreeImageTexture(arena_img.c_str(), month_texture, GL_TEXTURE0);

    glUniform1i(glGetUniformLocation(program, "textureEarth"), 0);

    //TODO: ADD NOISE TEXTURE

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    ///* fill to size of vertices */ {
    //    std::size_t vertices_size = mesh->vertices.size();
    //    std::size_t uvs_size = mesh->uvs.size();
    //    std::size_t normals_size = mesh->normals.size();
    //    if (uvs_size < vertices_size) {
    //        mesh->uvs.resize(vertices_size);
    //        for (std::size_t j = uvs_size; j < vertices_size; ++j) {
    //            mesh->uvs[j] = vec2(0.f, 0.f);
    //        }
    //    }
    //    if (normals_size < vertices_size) {
    //        mesh->normals.resize(vertices_size);
    //        for (std::size_t j = normals_size; j < vertices_size; ++j) {
    //            mesh->normals[j] = vec3(1.f, 1.f, 1.f);
    //        }
    //    }
    //}


    unsigned int vertices_bytes = mesh->vertices.size() * sizeof(vec4);
    unsigned int normals_bytes = mesh->normals.size() * sizeof(vec3);
    unsigned int uv_bytes = mesh->uvs.size() * sizeof(vec2);

    glBufferData(GL_ARRAY_BUFFER, vertices_bytes + normals_bytes, NULL, GL_STATIC_DRAW);
    unsigned int offset = 0;
    if (vertices_bytes > 0)
        glBufferSubData(GL_ARRAY_BUFFER, offset, vertices_bytes, &mesh->vertices[0]);
    offset += vertices_bytes;
    if (normals_bytes > 0)
        glBufferSubData(GL_ARRAY_BUFFER, offset, normals_bytes, &mesh->normals[0]);
    offset += normals_bytes;
    if (uv_bytes > 0)
        glBufferSubData(GL_ARRAY_BUFFER, offset, uv_bytes, &mesh->uvs[0]);

    glEnableVertexAttribArray(vNormal);
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vTexCoord);


    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_bytes));
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices_bytes + normals_bytes));

    //===== End: Send data to GPU ======


    // ====== Enable some opengl capabilitions ======
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 1.0);


    //===== Initalize some program state variables ======
    wireframe = false;
    //===== End: Initalize some program state variables ======

}

Mapping::Mapping()
{


}
