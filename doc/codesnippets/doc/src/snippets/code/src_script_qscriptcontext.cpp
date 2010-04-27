//! [0]
foo(20.5, "hello",  Object())
//! [0]


//! [1]
def Person_prototype_fullName(context, engine):
    self = context.selfObject()
    result = self.property("firstName").toString()
    result += QLatin1String(" ")
    result += self.property("lastName").toString()
    return result
//! [1]


//! [2]
def myInclude(ctx, eng):
    fileName = ctx.argument(0).toString()
    contents = readTheFile(fileName)
    ctx.setActivationObject(ctx.parentContext().activationObject())
    ctx.setThisObject(ctx.parentContext().selfObject())
    return eng.evaluate(contents, fileName)
//! [2]
