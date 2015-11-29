local exampleBlock = LuaBlockWrapper(BlockByID(2));
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
	spr:drawTextToScreen(exampleBlock:getBlockName(), 10, 10, 3, false);
	spr:drawTextToScreen(exampleBlock:getBlockUpdateInterval(), 10, 200, 2, false);
	exampleBlock:drawBlockToScreen(sprBatch, mainContentManager);
	
	if(frame / exampleBlock:getBlockUpdateInterval() >= exampleBlock:getTotalFrames() - 1) then
		frame = 0;
	end
end
