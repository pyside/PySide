//! [0]
if extension == Callable:
    context = argument
    engine = context.engine()
    sum = 0
    for i in range(0, context.argumentCount()):
        sum += context.argument(i).toNumber()
    return sum
//! [0]
