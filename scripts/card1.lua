--id =1

local function condition()
    print('con1')
    return true
end

local function action()
    add_score(1)
end

card1 = {
    trigger = Trigger.new(condition,action)
}
