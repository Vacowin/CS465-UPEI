//------------------------------------------------------------------------
// AIPathfinder
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class manages finding paths given a set of traversable nodes.
//------------------------------------------------------------------------

#ifndef AIPATHFINDER_H
#define AIPATHFINDER_H

#include "GameObjectManager.h"
#include "W_LineDrawer.h"
#include "tinyxml.h"
#include <list>
#include <vector>
#include <glm/glm.hpp>

namespace week2
{
	class AIPathfinder
	{
	public:
		//------------------------------------------------------------------------------
		// Public types.
		//------------------------------------------------------------------------------

		// A traversable node
		struct PathNode
		{
			glm::vec3 m_vPosition;
			std::vector<PathNode*> m_lNeighbourNodes;

			// Temporary cached values only relevant while calculating a path in FindPath. 
			// These are here to make searching more efficient.
			int G;
			int H;
			PathNode* pParentNode;
			bool bInOpenList;
			bool bInClosedList;
			bool bIsOccupied;

			PathNode() : G(0), H(0), pParentNode(NULL), bInOpenList(false), bInClosedList(false), bIsOccupied(false) {}
		};

		// Typedefs
		typedef std::vector<PathNode*> NodeList;
		typedef std::list<glm::vec3> PositionList;

	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		static void CreateInstance();
		static void DestroyInstance();
		static AIPathfinder* Instance();

		void Update();
		bool Load(const char* p_strPathfindingData);
		const PathNode* const GetClosestNode(const glm::vec3& p_vPosition);
		const PositionList& FindPath(const glm::vec3& p_vStart, const glm::vec3& p_vDestination);

		// Debug rendering
		void ToggleDebugRendering(Common::GameObjectManager* p_pGameObjectManager);
		void Render(const glm::mat4& p_mProj, const glm::mat4& p_mView);

		void UpdateNodeOccupied(const glm::vec3& p_vPos);
	private:
		//------------------------------------------------------------------------------
		// Private methods.
		//------------------------------------------------------------------------------

		// Constructor/Destructor are private because we're a Singleton
		AIPathfinder();
		~AIPathfinder();

	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------

		// Static singleton instance
		static AIPathfinder* s_pPathfindingInstance;

		// Complete node list
		NodeList m_lPathNodes;

		// Last path (stored for debug rendering)
		PositionList m_lLastPath;

		// Debugging
		bool m_bDebugRendering;
		wolf::LineDrawer* m_pLineDrawer;
	};
}

#endif // AIPATHFINDER_H

