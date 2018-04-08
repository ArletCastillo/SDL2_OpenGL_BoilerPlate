#include "renderer.hpp"

namespace Engine
{
	renderer::renderer()
	{

	}

	renderer::renderer(std::vector<vertex> pObjectVertices, std::vector<int> pObjectIndices)
	{
		fillOrLineDrawing = true;

		for (int i = 0; i < pObjectVertices.size(); i++)
		{
			mGameObjectVertices[i] = pObjectVertices[i];
		}

		for (int i = 0; i < pObjectIndices.size(); i++)
		{
			mGameObjectIndices[i] = pObjectIndices[i];
		}
	}


	renderer::~renderer()
	{
		/*glDeleteBuffers(1, &mVertexBufferObject);
		glDeleteBuffers(1, &mElementsBufferObject);
		glDeleteVertexArrays(1, &mVertexArrayObject);*/
	}

	void renderer::vertex_loader(int pFrameHeight, int pFrameWidth)
	{
		objects_generator();

		objects_activator();

		objects_atrributes_manager();

		glEnableVertexAttribArray(1);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		glUniform1i(glGetUniformLocation(mProgramID, "texture1"), 0);

		float resolution[] = { static_cast<float>(pFrameWidth), static_cast<float>(pFrameHeight) };
		glUniform2fv(glGetUniformLocation(mProgramID, "resolution"), 1, resolution);

	}

	void renderer::init_render(Engine::texture pObjectTexture)
	{
		mProgramID = mShaderManager.load_shaders("vertex.glsl", "frag.glsl");
		mGameObjectTexture = pObjectTexture;
	}

	void renderer::render()
	{
		//Use the program
		glUseProgram(mProgramID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mGameObjectTexture.get_texture());

		glBindVertexArray(mVertexArrayObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementsBufferObject);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glDrawElements(GL_TRIANGLES, sizeof(mGameObjectIndices), GL_UNSIGNED_INT, (void*)0);
	}

	void renderer::toggle_fill_or_line()
	{
		if (fillOrLineDrawing)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			fillOrLineDrawing = false;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			fillOrLineDrawing = true;
		}
	}


	void renderer::objects_generator()
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------

		glGenVertexArrays(1, &mVertexArrayObject);
		glGenBuffers(1, &mVertexBufferObject);
		glGenBuffers(1, &mElementsBufferObject);
	}


	void renderer::objects_activator()
	{
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(mVertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mGameObjectVertices), mGameObjectVertices, GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementsBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mGameObjectIndices), mGameObjectIndices, GL_STATIC_DRAW);
	}


	void renderer::objects_atrributes_manager()
	{
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			9 * sizeof(float),  // stride
			(void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			4,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			9 * sizeof(float),  // stride
			(void*)(3 * sizeof(float))          // array buffer offset
		);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			9 * sizeof(float),  // stride
			(void*)(7 * sizeof(float))          // array buffer offset
		);
		glEnableVertexAttribArray(2);
	}
}
