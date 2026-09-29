#include <iostream>
#include <string>
#include <stdexcept>

#include "custom_stack.h"

int main()
{
    std::cout << "====================================\n";
    std::cout << "     CustomStack Test Suite\n";
    std::cout << "====================================\n";


    // ==================================================
    // Test 1: Empty stack
    // ==================================================

    {
        std::cout << "\n[Test 1] Empty stack\n";

        CustomStack<int> stack;

        if (stack.empty() && stack.size() == 0)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 2: Push elements
    // ==================================================

    {
        std::cout << "\n[Test 2] Push elements\n";

        CustomStack<int> stack;

        stack.push(10);
        stack.push(20);
        stack.push(30);

        if (!stack.empty() && stack.size() == 3)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 3: Top element
    // ==================================================

    {
        std::cout << "\n[Test 3] Top element\n";

        CustomStack<int> stack;

        stack.push(10);
        stack.push(20);
        stack.push(30);

        if (stack.top() == 30)
        {
            std::cout << "PASS - Top = "
                      << stack.top() << '\n';
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 4: Pop
    // ==================================================

    {
        std::cout << "\n[Test 4] Pop element\n";

        CustomStack<int> stack;

        stack.push(10);
        stack.push(20);
        stack.push(30);

        stack.pop();

        if (stack.top() == 20 &&
            stack.size() == 2)
        {
            std::cout << "PASS - Top after pop = "
                      << stack.top() << '\n';
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 5: LIFO behavior
    // ==================================================

    {
        std::cout << "\n[Test 5] LIFO behavior\n";

        CustomStack<int> stack;

        stack.push(10);
        stack.push(20);
        stack.push(30);

        bool passed =
            stack.top() == 30;

        stack.pop();

        passed = passed &&
                 stack.top() == 20;

        stack.pop();

        passed = passed &&
                 stack.top() == 10;

        stack.pop();

        passed = passed &&
                 stack.empty();

        if (passed)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 6: Pop all elements
    // ==================================================

    {
        std::cout << "\n[Test 6] Pop all elements\n";

        CustomStack<int> stack;

        stack.push(10);
        stack.push(20);
        stack.push(30);

        stack.pop();
        stack.pop();
        stack.pop();

        if (stack.empty() &&
            stack.size() == 0)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 7: String stack
    // ==================================================

    {
        std::cout << "\n[Test 7] String stack\n";

        CustomStack<std::string> stack;

        stack.push("Hello");
        stack.push("C++");
        stack.push("Stack");

        if (stack.top() == "Stack" &&
            stack.size() == 3)
        {
            std::cout << "PASS - Top = "
                      << stack.top() << '\n';
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 8: top() on empty stack
    // ==================================================

    {
        std::cout << "\n[Test 8] top() on empty stack\n";

        CustomStack<int> stack;

        try
        {
            stack.top();

            std::cout << "FAIL - "
                      << "Exception was not thrown\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "PASS - "
                      << "out_of_range thrown\n";
        }
    }


    // ==================================================
    // Test 9: pop() on empty stack
    // ==================================================

    {
        std::cout << "\n[Test 9] pop() on empty stack\n";

        CustomStack<int> stack;

        try
        {
            stack.pop();

            std::cout << "FAIL - "
                      << "Exception was not thrown\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "PASS - "
                      << "out_of_range thrown\n";
        }
    }


    // ==================================================
    // Test 10: Repeated push/pop
    // ==================================================

    {
        std::cout << "\n[Test 10] Repeated push/pop\n";

        CustomStack<int> stack;

        for (int i = 1; i <= 1000; ++i)
        {
            stack.push(i);
        }

        bool passed = stack.size() == 1000;

        for (int i = 1000; i >= 1; --i)
        {
            if (stack.top() != i)
            {
                passed = false;
                break;
            }

            stack.pop();
        }

        passed = passed && stack.empty();
        passed = passed && stack.size() == 0;

        if (passed)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 11: Rvalue push
    // ==================================================

    {
        std::cout << "\n[Test 11] Rvalue push\n";

        CustomStack<std::string> stack;

        stack.push(std::string("Hello"));

        if (stack.top() == "Hello" &&
            stack.size() == 1)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }


    // ==================================================
    // Test 12: Lvalue push
    // ==================================================

    {
        std::cout << "\n[Test 12] Lvalue push\n";

        CustomStack<std::string> stack;

        std::string value = "C++";

        stack.push(value);

        if (stack.top() == "C++" &&
            stack.size() == 1)
        {
            std::cout << "PASS\n";
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }

// ==================================================
// Test 13: Non-const top() allows modification
// ==================================================

{
    std::cout << "\n[Test 13] Non-const top modification\n";

    CustomStack<int> stack;

    stack.push(10);

    stack.top() = 50;

    if (stack.top() == 50)
    {
        std::cout << "PASS - Top modified to "
                  << stack.top() << '\n';
    }
    else
    {
        std::cout << "FAIL\n";
    }
}

    // ==================================================
    // Final
    // ==================================================

    std::cout << "\n====================================\n";
    std::cout << "       All Tests Completed\n";
    std::cout << "====================================\n";

    return 0;
}