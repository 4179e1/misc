data = {name="lyre", age=32, handsome=true}

print (data.name)
print (data['name'])

data.website = "https://poetpalace.org"
data.handsome = false
data.name = nil
local age = data.age
print (data)

t = {[20]=100, ['name']='lyre', [3.14]='PI'}
print (t)

for k, v in pairs(t) do
    print(k, v)
end
