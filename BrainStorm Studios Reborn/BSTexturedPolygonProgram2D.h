#ifndef LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED
#define LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED

#include "BSShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include <map>



class BSTexturedPolygonProgram2D : public BSShaderProgram
{
public:

    BSTexturedPolygonProgram2D();

    bool loadProgram(std::string _path_vertex_shader, std::string _path_fragment_shader);

    void load_Shader_Attributes_Location(std::string theShaderAttributeText);
    void load_Shader_Uniforms_Location(std::string theShaderUniformText);

    void set_uniform(std::string _value_shader_name, float _value);
    void set_uniform(std::string _value_shader_name, float _value1, float _value2);
    void set_uniform(std::string _value_shader_name, float _value1, float _value2, float _value3);
    void set_uniform(std::string _value_shader_name, float _value1, float _value2, float _value3, float _value4);

    GLint get_location_from_shader(std::string _name);

private:
    std::map<std::string, GLint> locations_shader_values;
};

class BS_Available_Shaders
{
public:
    static std::string vertex_position()
    {
        return "BSVertexPosition3D";
    }
    static std::string texture_coordinates()
    {
        return "BSTextureCoordinates";
    }
    static std::string scale_size()
    {
        return "ScaleSize";
    }
    static std::string is_flake()
    {
        return "isFlake";
    }
    static std::string is_circle()
    {
        return "isCircle";
    }
    static std::string is_dark()
    {
        return "isDark";
    }
    static std::string circle_radius()
    {
        return "CircleRadius";
    }
    static std::string texture_color()
    {
        return "BSTextureColor";
    }
    static std::string texture_unit()
    {
        return "BSTextureUnit";
    }
    static std::string projection_matrix()
    {
        return "BSProjectionMatrix";
    }
    static std::string model_view_matrix()
    {
        return "BSModelViewMatrix";
    }
};


#endif // LTEXTUREDPOLYGONPROGRAM2D_H_INCLUDED
