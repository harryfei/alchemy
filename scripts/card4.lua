id = 4
local function condition()
    --add_score(1)
    return  true
end
local function action()
    add_score(4)
end
card4 = {}
card4.trigger = Trigger.new(condition,action)
