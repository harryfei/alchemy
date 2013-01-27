id =2
local function condition()
    print('con2')
    return true
end

local function action()
    add_score(3)
end

card2 = {
    trigger = Trigger.new(condition,action)
}
