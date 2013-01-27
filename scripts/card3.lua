id = 3

local function condition()
    --add_score(1)
    return false
end
local function action()
    add_score(3)
end
card3 = {}
card3.trigger = Trigger.new(condition,action)
