
local MyModule = {}

local function getname()
    return "lyre"
end

function MyModule.Greeting()
    print ("Hello, My name is "..getname())
end

return MyModule

