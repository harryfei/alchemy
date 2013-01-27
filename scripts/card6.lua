id = 6
local function condition()
    --add_score(1)
    return true
end
local function action()
    add_score(6)
end
card6 = {}
card6.trigger = Trigger.new(condition,action)
