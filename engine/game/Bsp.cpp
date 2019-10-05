#include "Bsp.h"

#include <iostream>

namespace bh {
    
Bsp::Bsp() {
    head = nullptr;
}

Bsp::Bsp(const std::vector<Tri3>& triangles) {
    head = build_bsp(triangles);
}

std::unique_ptr<node> Bsp::build_bsp(const std::vector<Tri3>& triangles) {
    if (triangles.size() == 0) {
        return nullptr;
    }
    //grab a random triangle
    int our_triangle_index = rand() % triangles.size();
    Tri3 our_triangle = triangles.at(our_triangle_index);
    //triangles.erase(triangles.begin() + our_triangle_index);

    //this is where our node is
    std::unique_ptr<node> our_node = std::make_unique<node>();
    our_node->triangle = our_triangle;
    
    //build up the front and back lists
    std::vector<Tri3> front;
    std::vector<Tri3> back;
    
    Vec3 plane_loc = our_triangle.a;
    Vec3 plane_dir = our_triangle.get_normal();
    for(int i = 0; i < triangles.size(); i++) {
        auto& triangle = triangles.at(i);
        if (i == our_triangle_index)
            continue;
        switch(triangle.in_front_of_plane(plane_loc, plane_dir)) {
            case Tri3::IN_FRONT_OF_PLANE::front:
                front.push_back(triangle);
            break;
            case Tri3::IN_FRONT_OF_PLANE::back:
                back.push_back(triangle);
            break;
            case Tri3::IN_FRONT_OF_PLANE::split:
            {
                static Tri3 splits[3];
                triangle.split_by_plane(plane_loc, plane_dir, splits);
                for (int i = 0; i < 3; i++) {
                    switch(splits[i].center_in_front_of_plane(plane_loc, plane_dir)) {
                        case Tri3::IN_FRONT_OF_PLANE::front:
                            front.push_back(splits[i]);
                            break;
                        case Tri3::IN_FRONT_OF_PLANE::back:
                            back.push_back(splits[i]);
                            break;
                        default:
                            std::cout << "error" << std::endl;
                            break;
                    }
                }
            }
            break;
        }
    }

    our_node->front = build_bsp(front);
    our_node->back = build_bsp(back);
    return our_node;
}

void render_single_triangle(const Camera& camera, sf::RenderWindow& window, const Tri3& triangle) {
    static bh::Tri2 projections[3];
    int num_triangles = bh::Camera::project_triangle(camera, triangle, projections);
    for(int i = 0; i < num_triangles; i++) {
        bh::Tri2::draw_to_screen(projections[i], window);
    }
}

void render_bsp_helper(const Camera& camera, sf::RenderWindow& window, const std::unique_ptr<node>& our_node) {
    if (our_node == nullptr)
        return;
    render_bsp_helper(camera, window, our_node->front);
    render_single_triangle(camera, window, our_node->triangle);
    render_bsp_helper(camera, window, our_node->back);
}

void Bsp::draw_bsp(const Camera& camera, sf::RenderWindow& window) const {
    render_bsp_helper(camera, window, head);
}

}
