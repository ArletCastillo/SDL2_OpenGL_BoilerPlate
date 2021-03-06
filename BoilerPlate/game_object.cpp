#include "component.hpp"
#include "game_object.hpp"

// STL
#include <algorithm>

namespace Engine
{
	namespace core
	{
		game_object::game_object()
			: mParent(nullptr)
			
		{}

		game_object::~game_object()
		{
			//// Delete all attached components
			////
			//while (!mComponents.empty()) delete mComponents.back(), mComponents.pop_back();

			//// Delete all attached children
			////
			//while (!mChildren.empty()) delete mChildren.back(), mChildren.pop_back();
		}

		void game_object::attach_component(component* pComponent)
		{
			pComponent->set_owner(this);
			mComponents.push_back(pComponent);
		}

		void game_object::remove_component(component* pComponent)
		{
			mComponents.erase(
				remove(mComponents.begin(), mComponents.end(), pComponent), mComponents.end()
			);

			delete pComponent;
		}

		void game_object::add_child(game_object* pChild)
		{
			// Set the child parent
			pChild->mParent = this;

			// 
			mChildren.push_back(pChild);
		}

		void game_object::remove_child(game_object* pChild)
		{
			mChildren.erase(
				remove(mChildren.begin(), mChildren.end(), pChild), mChildren.end()
			);

			delete pChild;
		}

		void game_object::update(double pDeltaTime)
		{
			// Update components
			//
			std::vector<component*>::iterator comp = mComponents.begin();
			for (; comp != mComponents.end(); ++comp)
			{
				(*comp)->update(pDeltaTime);
			}

			// Update children
			//
			std::vector<game_object*>::iterator child = mChildren.begin();
			for (; child != mChildren.end(); ++child)
			{
				(*child)->update(pDeltaTime);
			}

			// Base class function call
			//
			i_update::update(pDeltaTime);
		}

		void game_object::render()
		{
			//if ((mNupdates % 60) == 0)
			{
				// render children
				//
				std::vector<game_object*>::iterator child = mChildren.begin();
				for (; child != mChildren.end(); ++child)
				{
					(*child)->render();
				}
			}
		}

		void game_object::fill_vertices_info()
		{
		}

		void game_object::create_model_matrix()
		{
		}

		void game_object::create_position_vector()
		{
		}

		void game_object::move_object(Engine::math::Vector_4 pMoveVector)
		{
			this->get_components()[1]->get_model_matrix()->translate(pMoveVector);
			this->get_components()[2]->set_position(get_components()[2]->get_position() += pMoveVector);

		}

	}
}