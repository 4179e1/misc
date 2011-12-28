import odbchelper
print odbchelper.buildConnectionString
print getattr(odbchelper, "buildConnectionString")
object = odbchelper
method = "buildConnectionString"
print getattr(object, method)
print type(getattr(object, method))
import types
print type (getattr(object, method)) == types.FunctionType
print callable(getattr(object, method))
