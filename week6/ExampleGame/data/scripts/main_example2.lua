-------------------------------------------------------------------------------
-- main_example2.lua
--
-- Test script that sets up the scene for this week's sample code.
-------------------------------------------------------------------------------


local game = GetGame()
local gameObjectManager = game:GetGameObjectManager()
co = nil

-------------------------------------------------------------------------------
-- init
-------------------------------------------------------------------------------
function init()
	-- Create a game object
	gameObject = gameObjectManager:CreateGameObject()
	transform = gameObject:GetTransform()
	transform:Scale(0.05, 0.05, 0.05)
	
	-- Add a component renderable mesh
	componentRenderableMesh = CreateComponentRenderableMesh()
	componentRenderableMesh:Init("week5/ExampleGame/data/character/vincent.pod", "week5/ExampleGame/data/character/", "week5/ExampleGame/data/skinned.vsh", "week5/ExampleGame/data/skinned.fsh")
	gameObject:AddComponent(componentRenderableMesh)
	
	-- Add the character controller component
	componentCharacterController = CreateComponentCharacterController()
	local temp = componentCharacterController:IsActionComplete()
	gameObject:AddComponent(componentCharacterController)
	
	-- Everything initialized OK
	return true
end

-------------------------------------------------------------------------------
-- update
-------------------------------------------------------------------------------
function update(deltaTime)
	return true
end