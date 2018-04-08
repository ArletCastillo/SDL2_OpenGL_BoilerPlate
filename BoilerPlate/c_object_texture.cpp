#include "c_object_texture.hpp"

c_object_texture::c_object_texture()
{

}

c_object_texture::c_object_texture(std::string pName, const char * pTexturePath)
{
	Engine::core::component::component(pName);
	mTexture = Engine::texture::texture(pTexturePath);
}

Engine::texture c_object_texture::get_texture()
{
	return mTexture;
}