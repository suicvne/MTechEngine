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
	local maxX = math.ceil(800 / 32);
	for yIter=0,maxY,1 do
		for xIter=0,maxX,1 do
			local block = LuaBlockWrapper(BlockByID(1));
			block:setWorldX(xIter*32);
			block:setWorldY(yIter*32);
			table.insert(tableOfBlocks, block);
		end
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
	--io.write(table.getn(tableOfBlocks).."\n");
	for i=1,table.getn(tableOfBlocks) do
		tableOfBlocks[i]:setCurrentBlockFrame(frame / tableOfBlocks[i]:getBlockUpdateInterval());
		tableOfBlocks[i]:drawBlockToScreen(sprBatch, mainContentManager);		
	end

	if(frame / exampleBlock:getBlockUpdateInterval() >= 3) then
		frame = 0;
	end

	if(printKeyPressedMsg == true) then
		spr:drawTextToScreen(messageToPrintToScreen, 0, 600 - 32, 2, false);
	end

	spr:drawTextToScreen("Total blocks in table  " .. table.getn(tableOfBlocks) .. "\n", 2, 600 - 32, 2, false);
end
