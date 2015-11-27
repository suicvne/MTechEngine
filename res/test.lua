--io.write("Hey");

local b = LuaSpriteBatch(sprBatch);

local count = 0;
local toPrint = "Hey";

function onLoop()
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
