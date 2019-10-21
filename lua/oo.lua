Window_Prototype = {x=0, y=0, width=100, height=100}
MyWin = {title="Hello"}
setmetatable(MyWin, {__index = Window_Prototype})

print (MyWin.title)
print (MyWin.width)


Person={}
function Person:new(p)
    local obj = p
    if (obj == nil) then
        obj = {name="ChenHao", age=37, handsome=true}
    end
    self.__index = self
    return setmetatable(obj, self)
end
 
function Person:toString()
    return self.name .." : ".. self.age .." : ".. (self.handsome and "handsome" or "ugly")
end

me = Person:new()
print(me:toString())
 
kf = Person:new{name="King's fucking", age=70, handsome=false}
print(kf:toString())
