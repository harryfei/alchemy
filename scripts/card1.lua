--id =1

local function condition()
    print('con1')
    return true
end

local function action()
    add_score(1)
end

local trigger = Trigger.new(condition,action)
print(trigger)
print(trigger.hah)
trigger.ww = 1
print(trigger.ww)
card1 = {
    trigger = trigger
}
