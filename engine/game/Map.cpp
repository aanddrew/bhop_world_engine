#include "Map.h"
#include "../graphics/Tri2.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace bh {

//to help with parsing file, thanks CSCI 1300
void split(const std::string& temp, std::string filled[], char del, int max_words) {
    std::stringstream temp_stream(temp);
    int i = 0; 
    std::string sub_temp;
    while(std::getline(temp_stream, sub_temp, del)) {
        if (i == max_words)
            return;
        filled[i] = sub_temp;
        i++;
    }
}
    
Map::Map(const std::string& file_name) {
    //read in an obj file, and populate the array of triangles
    std::ifstream in_file(file_name);

    if(!in_file.is_open()) {
        std::string err_message = "ERROR: CANNOT OPEN MESH FILE: " + file_name + ".";
        throw std::invalid_argument(err_message);
        return;
    }
    std::vector<Vec3> temp_vertices;
    std::vector<Vec3> temp_normals;
    std::vector<int> temp_vertex_indeces;
    std::vector<int> temp_normal_indeces;
    std::string line;
    while(std::getline(in_file, line)) {
        if (line[0] == '#')
            continue;
        else if (line[0] == 'v') {
            if (line[1] == 'n') {
                std::string filled[4];
                split(line, filled, ' ', 4);
                temp_normals.push_back(
                    Vec3(
                        std::stof(filled[1]),
                        std::stof(filled[2]),
                        std::stof(filled[3])
                    )
                );

            }
            else if (line[1] == ' ') {
                std::string filled[4];
                split(line, filled, ' ', 4);
                temp_vertices.push_back(
                    Vec3(
                        std::stof(filled[1]),
                        std::stof(filled[2]),
                        std::stof(filled[3])
                    )
                );
            }
        }
        else if (line[0] == 'f') {
            std::string filled[4];
            split(line, filled, ' ', 4);
            for(int i = 1; i < 4; i++) {
                std::string filled_mini[3];
                split(filled[i], filled_mini, '/', 3);
                std::string vertex_string = filled_mini[0];
                std::string normal_string = filled_mini[2];
                temp_vertex_indeces.push_back(std::stoi(vertex_string) - 1);
                temp_normal_indeces.push_back(std::stoi(normal_string) - 1);
            }
        }
    }

    for(size_t i = 0; i < temp_vertex_indeces.size(); i+=3) {
        triangles.push_back(
            Tri3(
                temp_vertices.at(temp_vertex_indeces.at(i)),
                temp_vertices.at(temp_vertex_indeces.at(i+1)),
                temp_vertices.at(temp_vertex_indeces.at(i+2)),
                temp_normals.at(temp_normal_indeces.at(i + 1))
            )
        );
    }

    bsp = Bsp(triangles);
}

void Map::draw(const Camera& camera, sf::RenderWindow& window) const {
    //static bh::Tri2 projections[3];
    //for(auto& triangle : triangles) {
        //int num_triangles = bh::Camera::project_triangle(camera, triangle, projections);
        //for(int i = 0; i < num_triangles; i++) {
            //bh::Tri2::draw_to_screen(projections[i], window);
        //}
    //}
    bsp.draw_bsp(camera, window);
}

}
