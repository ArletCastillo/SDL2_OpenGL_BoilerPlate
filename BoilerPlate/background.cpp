#include "background.hpp"

namespace game 
{
	background::background()
	{
		fill_vertices_info();
		create_model_matrix();
		create_position_vector();
		mId = 5;
	}

	void background::fill_vertices_info()
	{
		vertices = new c_object_vertices("Vertices info");

		vertices->mVertices.push_back({ 2.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
		vertices->mVertices.push_back({ 2.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
		vertices->mVertices.push_back({ -2.0f,-2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
		vertices->mVertices.push_back({ -2.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });

		vertices->mIndices.push_back(0);
		vertices->mIndices.push_back(2);
		vertices->mIndices.push_back(3);
		vertices->mIndices.push_back(0);
		vertices->mIndices.push_back(1);
		vertices->mIndices.push_back(2);

		attach_component(vertices);
	}

	void background::create_model_matrix()
	{
		modelMatrix = new c_object_model_matrix("Object model matrix");
		attach_component(modelMatrix);
	}
	void background::create_position_vector()
	{
		position = new c_object_position("Object position");
		attach_component(position);
	}
}