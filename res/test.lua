local exampleBlock = LuaBlockWrapper(BlockByID(1));
local exampleBlock2 = LuaBlockWrapper(BlockByID(1));
local tableOfBlocks = {};
local spr = LuaSpriteBatch(sprBatch);
local cm = LuaContentManager(mainContentManager);
local timeoutMs = 3000;
local timeoutCounter = 0;
local messageToPrintToScreen = "kek";
local printKeyPressedMsg = false;
local frame = 0;

function onLoad()
	local maxY = math.ceil(600 / 32);
	io.write("Max Y is " .. maxY .. "\n");
	for yIter=0,maxY,32 do
		io.write("y: " .. yIter .. "\n");
		block = LuaBlockWrapper(BlockByID(1));
		block:setWorldX(0, yIter);
		table.insert(tableOfBlocks, block);
	end
end

function onUpdate()
	frame = frame + 1;
	if(printKeyPressedMsg == true) then
		timeoutCounter = timeoutCounter + 1;
	end
	if(timeoutCounter > timeoutMs) then
		timeoutCounter = 0;
	end
end

function onKeyDown(keycode)
	messageToPrintToScreen = "Key pressed   " .. keycode;
	printKeyPressedMsg = true;
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

	if(printKeyPressedMsg == true) then
		spr:drawTextToScreen(messageToPrintToScreen, 0, 600 - 32, 2, false);
	end
end
