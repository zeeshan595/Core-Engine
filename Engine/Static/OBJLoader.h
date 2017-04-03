#ifndef _OBJLOADER
#define _OBJLOADER

class ObjLoader
{
public:
    struct ObjStructure
    {
        std::vector<glm::vec3>          vertices;
        std::vector<glm::vec2>          uvs;
        std::vector<glm::vec3>          normals;

        std::vector<uint32_t>           indices;
    };

    static ObjStructure LoadObj(const char* filename)
    {
        //Setup
        ObjStructure                    output;
        std::vector<glm::vec2>          uvs;
        std::vector<glm::vec3>          normals;
        std::vector<std::string>        obj_line;
        uint32_t                        face_counter;
        //Open File
        std::ifstream in((MODEL_PATH + filename).c_str());
        if (!in.is_open())
        {
            std::cout << "Could not open file: " << filename << std::endl;
            return {};
        }
        //Create Buffer
        char buffer[1024];
        while(!in.eof())
        {
            //Get 1 Line & Store it in 'obj_line'
            in.getline(buffer, 1024);
            obj_line.push_back(std::string(buffer));
        }

        //Read each line and fill the data
        for (uint32_t i = 0; i < obj_line.size(); i++)
        {
            if (obj_line[i][0] == '#')
                continue;
            else if (obj_line[i][0] == 'v' && obj_line[i][1] == ' ')
            {
                float vx, vy, vz;
                sscanf(obj_line[i].c_str(), "v %f %f %f", &vx, &vy, &vz);
                output.vertices.push_back(glm::vec3(vx, vy, vz));
            }
            else if (obj_line[i][0] == 'v' && obj_line[i][1] == 't')
            {
                float tx, ty;
                sscanf(obj_line[i].c_str(), "vt %f %f", &tx, &ty);
                //Reason why 1 - ty
                //Open GL starts from top left of the texture
                //While others start bottom left
                uvs.push_back(glm::vec2(tx, 1.0f - ty));
            }
            else if (obj_line[i][0] == 'v' && obj_line[i][1] == 'n')
            {
                float nx, ny, nz;
                sscanf(obj_line[i].c_str(), "vn %f %f", &nx, &ny, &nz);
                normals.push_back(glm::vec3(nx, ny, nz));
            }
            else if (obj_line[i][0] == 'f' && obj_line[i][1] == ' ')
            {
                if (output.uvs.size() != output.vertices.size())
                    output.uvs.resize(output.vertices.size());

                if (output.normals.size() != output.vertices.size())
                    output.normals.resize(output.vertices.size());

                //FV = vertex index
                //FU = UV index
                //FN = Normal index
                uint32_t fv1, fu1, fn1, fv2, fu2, fn2, fv3, fu3, fn3;
                sscanf(obj_line[i].c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &fv1, &fu1, &fn1, &fv2, &fu2, &fn2, &fv3, &fu3, &fn3);
                //File index 1 is actually 0 so we subtract 1 from everything
                fv1--; fu1--; fn1--; fv2--; fu2--; fn2--; fv3--; fu3--; fn3--;
                //This converts each indices array (vertex, uvs, normals) into 1 indices array
                output.uvs[fv1] = uvs[fu1];
                output.uvs[fv2] = uvs[fu2];
                output.uvs[fv3] = uvs[fu3];

                output.normals[fv1] = normals[fn1];
                output.normals[fv2] = normals[fn2];
                output.normals[fv3] = normals[fn3];
                
                output.indices.push_back(fv1);
                output.indices.push_back(fv2);
                output.indices.push_back(fv3);
            }
        }

        //Return output
        return output;
    }
};

#endif