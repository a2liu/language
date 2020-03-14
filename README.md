# Ideas to Include in a new Programming Language
Focus is on programmer ergonomics. Should be as easy to use as python and as fast
as Java.

1. Heavy type inference; type inference of variables, and also of function parameters
   and return type; interfaces are made for every individual method, and also for
   every method combination that is inferred. Classes don't inherit from other classes,
   instead they inherit from interfaces, and the implementation is copied over.
2. Operator overloads - supported via interfaces, uses function with special name
   plus decorator
3. Python syntax
4. Inheritance uses interfaces, allows for multiple inheritance
5. Compile-time errors are reported but only stop execution if they're on a potential
   runtime path.
6. Error-reporting can be turned on and off again at will
7. Imports work like python
8. Execution order works like python, but function names do not have to be
   written in order
9. Casts are inserted whenever necessary, but emit a warning.
0. Class meta-types
1. Match statements; supports match on class of object
2. Generators, coroutines, asyncio, all supported
3. implicit return of None
4. Shadowing is not allowed, except accross function boundaries
5. Variables are implicitly initialized to none
6. If, Else, etc. do not produce a new scope.

## Examples

```python
def function():
  pass

print("Hello, world!")

class A()<In, Out>:
  pass
```

Should translate to the following java code:

```java
public class Script {
  public class Function0 {
    public Object call() {
      return null;
    }
  }

  public class A<In, Out> {}

  public static Function0 function;
  public static Class<? extends Object> classA;

  static {
    function = new Function0;

    System.out.println("Hello, world!");

    classA = A.class;
  }
}
```

