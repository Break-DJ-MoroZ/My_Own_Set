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
					set.head_ = nullptr;
				}
			}
			else 
			{
				Node* temp = head_;

				if (set.head_->key_ < temp->key_)
				{
					Node* tempPtr = set.head_->next_;
					head_ = set.head_;
					set.head_->next_ = temp;
					set.head_ = tempPtr;
				}
				else if (set.head_->key_ == temp->key_)
				{
					Node* tempPtr = set.head_->next_;
					delete set.head_;
					set.head_->next_ = tempPtr;
				}
				while (set.head_ && temp->next_)
				{
					if (set.head_->key_ == temp->key_)
					{
						Node* tempPtr = set.head_->next_;
						delete set.head_;
						set.head_ = tempPtr;
					}
					else if (set.head_->key_ > (temp->next_)->key_)
					{
						Node* tempPtr = set.head_->next_;
						Node* thisPtr = temp->next_;
						temp->next_ = set.head_;
						(temp->next_)->next_ = thisPtr;
						set.head_ = tempPtr;
					}
					else
					{
						temp = temp->next_;
					}
				}
				if (!temp->next_)
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

	bool b = a.search(-12);
	a.insert(0);
	a.insert(-10);
	a.insert(1);
	a.insert(-7);
	a.insert(-8);
	a.insert(13);
	a.insert(13);
	a.insert(14);
	a.insert(-10);
	a.insert(-8);
	a.insert(28);
	a.insert(12);
	a.insert(0);
	a.insert(12);

	b = a.search(-10);
	b = a.search(0);
	b = a.search(-11);
	b = a.search(0);
	b = a.search(12);
	b = a.search(-98);
	b = a.search(128);
	b = a.search(28);
	b = a.search(-17);

	a.deleteKey(-8);
	a.deleteKey(-12);
	a.deleteKey(29);
	a.deleteKey(-10);
	a.deleteKey(28);
	a.deleteKey(-8);
	a.deleteKey(0);

	Set<int> c = a;

	c.deleteKey(-7);
	c.deleteKey(1);

	a = Set<int>(c);

	a.insert(54);
	a.insert(-2);
	a.insert(-1);
	a.insert(0);

	//a.deleteKey(12);
	a.deleteKey(14);

	c.deleteKey(13);

	//a.insert(-1);
	//a.insert(19);

	c.merge(a);

	return 0;
}