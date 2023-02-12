#include <iostream>

template <class Type>
class Set
{
public:
	Set():
		head_(nullptr)
	{}

	Set(const Set& set):
		head_(nullptr)
	{
		if (this != &set)
		{
			Node* temp = set.head_;
			if (temp)
			{
				head_ = new Node(temp->key_);
				Node* thisTemp = head_;
				temp = temp->next_;

				while (temp && thisTemp)
				{
					thisTemp->next_ = new Node(temp->key_);
					thisTemp = thisTemp->next_;
					temp = temp->next_;
				}
			}
		}
	}

	Set operator= (const Set& set) noexcept
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

	Set(Set&& set) noexcept :
		head_(nullptr)
	{
		head_ = set.head_;
		set.head_ = nullptr;
	}

	Set operator= (Set&& set) noexcept
	{
		Node* temp = set.head_;
		set.head_ = head_;
		head_ = temp;

		return *this;
	}

	~Set()
	{
		while (head_)
		{
			Node* temp = head_;
			head_ = head_->next_;
			delete temp;
		}
	}

	void insert(const Type& key)
	{
		Node* temp = head_;

		bool isUnique = true;

		if (!temp)
		{
			head_ = new Node(key);
		}
		else if (key < temp->key_)
		{
			head_ = new Node(key, temp);
		}
		else if (key > temp->key_)
		{
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

	bool search(const Type& key) const
	{
		bool isInSet = false;
		Node* temp = head_;

		if (temp && key < temp->key_)
		{
			temp = nullptr;
		}

		while (temp && !isInSet)
		{
			(key == temp->key_)? isInSet = true : temp = temp->next_;
		}

		return isInSet;
	}

	void deleteKey(const Type& key)
	{
		bool isInSet = true;

		Node* temp = head_;

		if (temp)
		{
			if (key < temp->key_)
			{
				std::cout << "There is no this key in the set!\n";
				isInSet = false;
			}
			else if (key == temp->key_)
			{
				head_ = temp->next_;
				delete temp;
				isInSet = false;
			}
			else
			{
				while (isInSet)
				{
					if (!(temp->next_))
					{
						std::cout << "There is no this key in the set!\n";
						isInSet = false;
					}
					else if (key == (temp->next_)->key_)
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
		else
		{
			std::cout << "There are not items in the set!\n";
		}
	}

	Set& merge(Set& set)
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
							set.deleteKey(set.head_->key_);
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
};

int main()
{
	Set<int> a;
	Set<int> b;
	Set<int> c;

	a.insert(0);
	a.insert(3);
	a.insert(6);
	a.insert(20);

	c.insert(-10);
	c.insert(-9);
	c.insert(-8);
	c.insert(-7);
	c.insert(-6);

	c.insert(1);
	c.insert(2);
	c.insert(5);
	c.insert(6);
	c.insert(7);
	c.insert(19);
	c.insert(20);
	c.insert(21);

	c.merge(a);

	b.insert(3);
	b.insert(5);

	b.merge(c);

	return 0;
}