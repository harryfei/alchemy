--id =1

local function condition()
    return true
end

local function action()
    add_score(1)
end

local trigger = Trigger.new(condition,action)
card1 = {
    trigger = trigger
}
