--io.write("Hey");

local b = LuaSpriteBatch(sprBatch);
local testTexture = b:loadTexture("rayquaza.png");
local count = 0;
local toPrint = "Hey";

local xx = 69;
local yy = 69;
local moveBackwards = false;

function onLoop()

  if(moveBackwards) then
    xx = xx - 1;
    yy = yy - 1;
  else
    xx = xx + 1;
    yy = yy + 1;
  end

  if(xx > 900) then
    moveBackwards = true;
  end
  if(yy > 900) then
    moveBackwards = true;
  end
  if(xx < 4) then
    moveBackwards = false;
  end
  if(yy > 4) then
    moveBackwards = false;
  end

  if(testTexture ~= nil) then
    b:drawTextureToScreen(testTexture, math.sqrt(xx), math.sqrt(yy));
  end

  --b:drawTextToScreen(count, 0, 100, 2, false);
  b:drawTextToScreen(toPrint, 10, 10, 3, true);
  count = count + 1;
  if(count > 50) then
    toPrint = "";
  end
  if(count > 100) then
    toPrint = "Hey";
    count = 0;
  end
end
