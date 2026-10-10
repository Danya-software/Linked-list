#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int value) {
        val = value;
        next = nullptr;
    }
};

ListNode* createList(int n) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        ListNode* node = new ListNode(value);

        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void printList(ListNode* head) {
    cout << "[";
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) cout << ", ";
        current = current->next;
    }
    cout << "]\n";
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

ListNode* getNodeAt(ListNode* head, int index) {
    int currentIndex = 0;
    while (head != nullptr && currentIndex < index) {
        head = head->next;
        currentIndex++;
    }
    return head;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    tail->next = (list1 != nullptr) ? list1 : list2;
    return dummy.next;
}

ListNode* deleteDuplicates(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->val == current->next->val) {
            ListNode* duplicate = current->next;
            current->next = duplicate->next;
            delete duplicate;
        } else {
            current = current->next;
        }
    }
    return head;
}

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

ListNode* reverseList(ListNode* head) {
    ListNode* previous = nullptr;
    ListNode* current = head;

    while (current != nullptr) {
        ListNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }
    return previous;
}

void reorderList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return;

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* second = reverseList(slow->next);
    slow->next = nullptr;
    ListNode* first = head;

    while (second != nullptr) {
        ListNode* firstNext = first->next;
        ListNode* secondNext = second->next;
        first->next = second;
        second->next = firstNext;
        first = firstNext;
        second = secondNext;
    }
}

void deleteNode(ListNode* node) {
    if (node == nullptr || node->next == nullptr) return;
    ListNode* nextNode = node->next;
    node->val = nextNode->val;
    node->next = nextNode->next;
    delete nextNode;
}

ListNode* doubleIt(ListNode* head) {
    ListNode* reversed = reverseList(head);
    ListNode* current = reversed;
    int carry = 0;

    while (current != nullptr) {
        int doubled = current->val * 2 + carry;
        current->val = doubled % 10;
        carry = doubled / 10;
        current = current->next;
    }

    if (carry > 0) {
        ListNode* tail = reversed;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = new ListNode(carry);
    }

    return reverseList(reversed);
}

ListNode* mergeRange(ListNode** lists, int left, int right) {
    if (left > right) return nullptr;
    if (left == right) return lists[left];

    int middle = left + (right - left) / 2;
    ListNode* first = mergeRange(lists, left, middle);
    ListNode* second = mergeRange(lists, middle + 1, right);
    return mergeTwoLists(first, second);
}

ListNode* mergeKLists(ListNode** lists, int k) {
    if (k == 0) return nullptr;
    return mergeRange(lists, 0, k - 1);
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr || k <= 1) return head;

    ListNode dummy(0);
    dummy.next = head;
    ListNode* groupPrevious = &dummy;

    while (true) {
        ListNode* kth = groupPrevious;
        for (int i = 0; i < k && kth != nullptr; i++) {
            kth = kth->next;
        }
        if (kth == nullptr) break;

        ListNode* groupNext = kth->next;
        ListNode* previous = groupNext;
        ListNode* current = groupPrevious->next;

        while (current != groupNext) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        ListNode* oldGroupStart = groupPrevious->next;
        groupPrevious->next = kth;
        groupPrevious = oldGroupStart;
    }

    return dummy.next;
}

ListNode* partition(ListNode* head, int x) {
    ListNode lessDummy(0);
    ListNode greaterDummy(0);
    ListNode* lessTail = &lessDummy;
    ListNode* greaterTail = &greaterDummy;

    while (head != nullptr) {
        ListNode* nextNode = head->next;
        head->next = nullptr;

        if (head->val < x) {
            lessTail->next = head;
            lessTail = head;
        } else {
            greaterTail->next = head;
            greaterTail = head;
        }
        head = nextNode;
    }

    lessTail->next = greaterDummy.next;
    return lessDummy.next;
}

void showMenu() {
    cout << "\n=== Linked List: лабораторна робота ===\n";
    cout << "1. Об'єднати два відсортовані списки\n";
    cout << "2. Видалити дублікати з відсортованого списку\n";
    cout << "3. Перевірити наявність циклу\n";
    cout << "4. Перевпорядкувати список\n";
    cout << "5. Видалити вузол за значенням (не останній)\n";
    cout << "6. Подвоїти число у вигляді списку\n";
    cout << "7. Об'єднати k відсортованих списків\n";
    cout << "8. Розвернути вузли в k-групі\n";
    cout << "9. Розділити список за значенням x\n";
    cout << "0. Вийти\n";
    cout << "Ваш вибір: ";
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) return 0;

        if (choice == 1) {
            int n, m;
            cout << "Кількість елементів першого списку: ";
            cin >> n;
            cout << "Введіть елементи першого списку у відсортованому порядку: ";
            ListNode* list1 = createList(n);
            cout << "Кількість елементів другого списку: ";
            cin >> m;
            cout << "Введіть елементи другого списку у відсортованому порядку: ";
            ListNode* list2 = createList(m);
            ListNode* result = mergeTwoLists(list1, list2);
            cout << "Результат: "; printList(result);
            deleteList(result);
        } else if (choice == 2) {
            int n;
            cout << "Кількість елементів: "; cin >> n;
            cout << "Введіть відсортований список: ";
            ListNode* head = createList(n);
            head = deleteDuplicates(head);
            cout << "Результат: "; printList(head);
            deleteList(head);
        } else if (choice == 3) {
            int n, pos;
            cout << "Кількість вузлів: "; cin >> n;
            cout << "Введіть значення вузлів: ";
            ListNode* head = createList(n);
            cout << "Індекс вузла для циклу (-1, якщо циклу немає): "; cin >> pos;
            ListNode* tail = head;
            while (tail != nullptr && tail->next != nullptr) tail = tail->next;
            if (tail != nullptr && pos >= 0) {
                ListNode* target = getNodeAt(head, pos);
                if (target != nullptr) tail->next = target;
            }
            cout << (hasCycle(head) ? "Цикл є: true\n" : "Циклу немає: false\n");
            if (tail != nullptr) tail->next = nullptr;
            deleteList(head);
        } else if (choice == 4) {
            int n;
            cout << "Кількість елементів: "; cin >> n;
            cout << "Введіть елементи: ";
            ListNode* head = createList(n);
            reorderList(head);
            cout << "Результат: "; printList(head);
            deleteList(head);
        } else if (choice == 5) {
            int n, value;
            cout << "Кількість елементів: "; cin >> n;
            cout << "Введіть елементи списку: ";
            ListNode* head = createList(n);
            cout << "Значення вузла, який потрібно видалити (не останній): "; cin >> value;
            ListNode* target = head;
            while (target != nullptr && target->val != value) target = target->next;
            if (target == nullptr || target->next == nullptr) {
                cout << "Помилка: вузол не знайдений або він останній.\n";
            } else {
                deleteNode(target);
                cout << "Результат: "; printList(head);
            }
            deleteList(head);
        } else if (choice == 6) {
            int n;
            cout << "Кількість цифр: "; cin >> n;
            cout << "Введіть цифри числа: ";
            ListNode* head = createList(n);
            head = doubleIt(head);
            cout << "Подвоєне число: "; printList(head);
            deleteList(head);
        } else if (choice == 7) {
            int k;
            cout << "Кількість списків k: "; cin >> k;
            ListNode** lists = new ListNode*[k];
            for (int i = 0; i < k; i++) {
                int n;
                cout << "Кількість елементів списку " << i + 1 << ": "; cin >> n;
                cout << "Введіть відсортовані елементи: ";
                lists[i] = createList(n);
            }
            ListNode* result = mergeKLists(lists, k);
            cout << "Результат: "; printList(result);
            deleteList(result);
            delete[] lists;
        } else if (choice == 8) {
            int n, k;
            cout << "Кількість елементів: "; cin >> n;
            cout << "Введіть елементи: ";
            ListNode* head = createList(n);
            cout << "Розмір групи k: "; cin >> k;
            if (k < 1) cout << "k має бути додатним.\n";
            else {
                head = reverseKGroup(head, k);
                cout << "Результат: "; printList(head);
            }
            deleteList(head);
        } else if (choice == 9) {
            int n, x;
            cout << "Кількість елементів: "; cin >> n;
            cout << "Введіть елементи: ";
            ListNode* head = createList(n);
            cout << "Значення x: "; cin >> x;
            head = partition(head, x);
            cout << "Результат: "; printList(head);
            deleteList(head);
        } else if (choice != 0) {
            cout << "Невірний пункт меню. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}
