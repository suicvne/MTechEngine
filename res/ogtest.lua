--[[
	This is the "stress" test I created to test the Lua engine. But it's kinda boring so
]]

--io.write("Hey");

local b = LuaSpriteBatch(sprBatch);
local cm = LuaContentManager(mainContentManager);

local testTexture = cm:getTexture("r");
--local testTexture = b:loadTexture("rayquaza.png");
local bgTest = LuaSDL_Texture(b:loadTexture("bg_test.png"));
cm:addTexture("bg", b:loadTexture("bg_test.png"));

local count = 0;
local toPrint = "--RAYQUAZA INTENSIFIES--";

local xx = 69;
local yy = 69;
local _trueX = 0;
local _trueY = 0;
local moveBackwards = false;

local CONST_MOVE_AMOUNT = 50;

function onUpdate()
  count = count + 3;
  if(count > 50) then
    toPrint = "";
  end
  if(count > 100) then
    toPrint = "--RAYQUAZA INTENSIFIES--";
    count = 0;
  end

  if(moveBackwards) then
    xx = xx - CONST_MOVE_AMOUNT;
    yy = yy - CONST_MOVE_AMOUNT;
  else
    xx = xx + CONST_MOVE_AMOUNT;
    yy = yy + CONST_MOVE_AMOUNT;
  end

  if(xx > 600) then
    moveBackwards = true;
  end
  if(yy > 600) then
    moveBackwards = true;
  end
  if(xx < 69) then
    moveBackwards = false;
  end
  if(yy < 69) then
    moveBackwards = false;
  end

  _trueX = math.sqrt(xx);
  _trueY = math.sqrt(yy);
end

function onLoop()
  b:drawTextureToScreenScaled(cm:getTexture("bg"), 0, 0, 0.7);
  if(testTexture ~= nil) then
    b:drawTextureToScreen(testTexture, _trueX, _trueY);
  end

  --b:drawTextToScreen(count, 0, 100, 2, false);
  b:drawTextToScreen(toPrint, 10, 10, 3, false);
end

