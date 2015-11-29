local exampleBlock = LuaBlockWrapper(BlockByID(1));
local exampleBlock2 = LuaBlockWrapper(BlockByID(2));
local spr = LuaSpriteBatch(sprBatch);
local cm = LuaContentManager(mainContentManager);

local frame = 0;
function onUpdate()
	frame = frame + 1;
end

function onLoop()
	exampleBlock:setCurrentBlockFrame(frame / exampleBlock:getBlockUpdateInterval());
	exampleBlock:setWorldX(100);
	exampleBlock:setWorldY(100);
	exampleBlock2:setWorldX(132);
	exampleBlock2:setWorldY(100);
	spr:drawTextToScreen(exampleBlock:getBlockName(), 10, 10, 3, false);
	spr:drawTextToScreen(exampleBlock:getBlockUpdateInterval(), 10, 200, 2, false);
	exampleBlock:drawBlockToScreen(sprBatch, mainContentManager);
	exampleBlock2:drawBlockToScreen(sprBatch, mainContentManager);
	
	if(frame / exampleBlock:getBlockUpdateInterval() >= exampleBlock:getTotalFrames() - 1) then
		frame = 0;
	end
end
