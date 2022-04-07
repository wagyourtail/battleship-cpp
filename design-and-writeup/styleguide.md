
# Styleguide

## Introduction

In order to make the codebase more readable, we use a style guide.

## Files

Each class in the codebase must have its own file.
supporting enums and structs are allowed to share the file,
or be in a file where the "class" is a namespace.

## Folders

classes are grouped in folders, there groupings should be for related classes, but don't nececairily require a
equivalently named namespace.

## Forward References

Forward References should be avoided when possible, it is *always* preferable to use the `#include` directive.

## Spaces

4 spaces, not tabs.

## Indentation

indentation should occur on every hierarchical thing, (ie class scope operators, case, inside curly braces, etc).
ie
```cpp
class Foo {
    private:
        int bar;
};
```

## Whitespace

whitespace should be blank lines between important statements for readability...
for example, before a function definition, before a class definition, before a namespace definition, etc.
there don't need to be a blank line between stubs, or between a function definition and its body.

generally, blank lines should be before any line with opening curly braces or a colon in it, or after a closing curly brace.

## Line Length

120

## if statements and braces

if an if statement doesn't use curly braces its contents should be on the same line,
if the contents are too long to do this due to line length,
then the contents should be on the next line and use curly braces.

```cpp
// allowed
if (foo) bar();
else baz();

// not allowed
if (foo)
    bar();
else
    baz();

// allowed
if (foo) {
    bar();
} else {
    baz();
}
```

## Capitialization and Var names

Most things are camelCase, namespaces, classes and enums should be PascalCase.
variables are mostly camelCase, but if it's a direct reference to a C variable/concept,
it is allowed to be snake_case. `static/const` variables should be SCREAMING_SNAKE_CASE.

