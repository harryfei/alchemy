id = 5
local function condition()
    --add_score(1)
    return false
end
local function action()
    add_score(5)
end
card5 = {}
card5.trigger = Trigger.new(condition,action)
