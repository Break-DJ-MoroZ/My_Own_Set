#ifndef SET_H
#define SET_H

template <class Type>
class Set
{
public:
    Set():
            head_(nullptr)
    {}

    Set(const Set& set);

    Set operator= (const Set& set) noexcept;

    Set(Set&& set) noexcept;

    Set operator= (Set&& set) noexcept;

    ~Set()
    {
        while (head_)
        {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }

    void insert(const Type& key);

    bool search(const Type& key) const;

    void deleteKey(const Type& key);

    Set& merge(Set& set);

    Set& substract(const Set& set);

    template<class FriendType>
    friend Set<FriendType> getIntersection(const Set<FriendType>& first, const Set<FriendType>& second);

private:

    struct Node
    {
        Node(const Type& data, Node* next = nullptr) :
                key_(data),
                next_(next)
        {}
        Type key_;
        Node* next_;
    };

    Node* head_;

    void swap(Set& set)
    {
        std::swap(head_, set.head_);
    }
};





template <class Type>
Set<Type>::Set(const Set& set):
        head_(nullptr)
{
    if (this != &set && set.head_)
    {
        head_ = new Node(set.head_->key_);

        Node* thisTemp = head_;
        Node* temp = set.head_;
        temp = temp->next_;

        while (temp)
        {
            thisTemp->next_ = new Node(temp->key_);
            thisTemp = thisTemp->next_;
            temp = temp->next_;
        }
    }
}

template<class Type>
Set<Type> Set<Type>::operator= (const Set<Type>& set) noexcept
{
    if (this != &set)
    {
        Set tempObj(set);
        Node* tempPtr = tempObj.head_;
        tempObj.head_ = head_;
        head_ = tempPtr;
    }

    return *this;
}

template <class Type>
Set<Type>::Set(Set&& set) noexcept :
        head_(nullptr)
{
    swap(set);
}

template <class Type>
Set<Type> Set<Type>::operator= (Set&& set) noexcept
{
    swap(set);
    return *this;
}

template<class Type>
void Set<Type>::insert(const Type& key)
{
    if (!head_)
    {
        head_ = new Node(key);
    }
    else if (key < head_->key_)
    {
        head_ = new Node(key, head_);
    }
    else if (key > head_->key_)
    {
        Node* temp = head_;

        bool isUnique = true;

        while (isUnique)
        {
            if (!(temp->next_))
            {
                temp->next_ = new Node(key);
                isUnique = false;
            }
            else if (key == (temp->next_)->key_)
            {
                isUnique = false;
            }
            else if (key < (temp->next_)->key_)
            {
                temp->next_ = new Node(key, temp->next_);
                isUnique = false;
            }
            else
            {
                temp = temp->next_;
            }
        }
    }
}

template <class Type>
bool Set<Type>::search(const Type& key) const
{
    bool isInSet = false;

    if (!head_ || (key >= head_->key_))
    {
        Node* temp = head_;

        while (temp && !isInSet)
        {
            //(key == temp->key_) ? isInSet = true : temp = temp->next_;
            if (key == temp->key_)
            {
                isInSet = true;
            }
            else
            {
                temp = temp->next_;
            }
        }
    }

    return isInSet;
}

template <class Type>
void Set<Type>::deleteKey(const Type& key)
{
    if (head_)
    {
        Node* temp = head_;

        if (key == head_->key_)
        {
            head_ = head_->next_;
            delete temp;
        }
        else if (key > temp->key_)
        {
            bool isInSet = true;

            while (isInSet && temp->next_)
            {
                if (key == (temp->next_)->key_)
                {
                    Node* deletThisItem = temp->next_;
                    temp->next_ = (temp->next_)->next_;
                    delete deletThisItem;

                    isInSet = false;
                }
                else
                {
                    temp = temp->next_;
                }
            }
        }
    }
}

template <class Type>
Set<Type>& Set<Type>::merge(Set& set)
{
    if (set.head_)
    {
        if (!head_)
        {
            std::swap(head_, set.head_);
        }
        else if (!set.head_->next_)
        {
            Node* temp = head_;

            if (set.head_->key_ < temp->key_)
            {
                head_ = set.head_;
                head_->next_ = temp;
            }
            else if (temp->next_)
            {
                while (set.head_ && temp->next_)
                {
                    if (set.head_->key_ == (temp->next_)->key_)
                    {
                        delete set.head_;
                        set.head_ = nullptr;
                    }
                    else if (set.head_->key_ < (temp->next_)->key_)
                    {
                        Node* setTemp = set.head_->next_;
                        set.head_->next_ = temp->next_;
                        temp->next_ = set.head_;
                        set.head_ = setTemp;
                    }
                    temp = temp->next_;
                }
                if (!temp->next_)
                {
                    temp->next_ = set.head_;
                }
            }
            set.head_ = nullptr;
        }
        else
        {
            Node* temp = head_;
            Node* setTemp = set.head_;

            if (set.head_->key_ < head_->key_)
            {
                while ((setTemp->next_)->key_ < temp->key_)
                {
                    setTemp = setTemp->next_;
                }
                head_ = set.head_;
                set.head_ = setTemp->next_;
                setTemp->next_ = temp;
            }
            setTemp = set.head_;

            if (temp->key_ == setTemp->key_)
            {
                set.head_ = setTemp->next_;
                delete setTemp;
                setTemp = set.head_;
            }

            while (temp->next_ && setTemp)
            {
                if (setTemp->key_ < (temp->next_)->key_)
                {
                    set.head_ = setTemp->next_;
                    setTemp->next_ = temp->next_;
                    temp->next_ = setTemp;
                    setTemp = set.head_;
                    temp = temp->next_;
                }
                else if (setTemp->key_ == (temp->next_)->key_)
                {
                    set.head_ = setTemp->next_;
                    delete setTemp;
                    setTemp = set.head_;
                }
                else
                {
                    temp = temp->next_;
                }
            }
            setTemp = set.head_;

            if (!temp->next_ && setTemp)
            {
                temp->next_ = set.head_;
                set.head_ = nullptr;
            }
        }
    }

    return *this;
}

template <class Type>
Set<Type>& Set<Type>::substract(const Set& set)
{
    if (head_ && set.head_)
    {
        Node* temp = head_;
        Node* setTemp = set.head_;

        if (!(temp->next_ && setTemp->next_) && (head_->key_ == set.head_->key_))
        {
            delete head_;
        }
        else
        {
            while (temp && setTemp && (setTemp->key_ <= temp->key_))
            {
                if (setTemp->key_ < temp->key_)
                {
                    setTemp = setTemp->next_;
                }
                else
                {
                    head_ = temp->next_;
                    delete temp;
                    temp = head_;
                    setTemp = setTemp->next_;
                }
            }

            while (temp->next_ && setTemp)
            {
                if (setTemp->key_ < (temp->next_)->key_)
                {
                    setTemp = setTemp->next_;
                }
                else if (setTemp->key_ > (temp->next_)->key_)
                {
                    temp = temp->next_;
                }
                else
                {
                    Node* deletedTemp = temp->next_;
                    temp->next_ = (temp->next_)->next_;
                    delete deletedTemp;
                }
            }
        }
    }

    return *this;
}

template<class FriendType>
Set<FriendType> getIntersection(const Set<FriendType>& first, const Set<FriendType>& second)
{
    Set<FriendType> newSet;

    Node* firstTemp = first.head_;
    Node* secondTemp = second.head_;

    while (firstTemp && secondTemp)
    {
        if (firstTemp->key_ > secondTemp->key_)
        {
            secondTemp = secondTemp->next_;
        }
        else if (firstTemp->key_ < secondTemp->key_)
        {
            firstTemp = firstTemp->next_;
        }
        else
        {
            newSet.insert(firstTemp->key_);
            secondTemp = secondTemp->next_;
            firstTemp = firstTemp->next_;
        }
    }

    return newSet;
}

#endif //SET_H
