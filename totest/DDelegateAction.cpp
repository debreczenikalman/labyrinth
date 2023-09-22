/// <summary>
/// Delegate action, containing the pointer to a function and other information
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template<class Return, class... Params>
class DDelegateAction
{
public:
	DDelegateAction()
	{
        this->functionPointer = nullptr;
		ID = 0;
		timesCalled = 0;
	}
	DDelegateAction(int ID)
	{
        this->functionPointer = nullptr;
		this->ID = ID;
		timesCalled = 0;
	}
	DDelegateAction(Return(*function)(Params...), int ID)
	{
		this->functionPointer = function;
		this->ID = ID;
		timesCalled = 0;
	}
	DDelegateAction(Return(*function)(Params...))
	{
		this->functionPointer = function;
		this->ID = 0;
		timesCalled = 0;
	}
	~DDelegateAction()
	{

	}

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	Return Fire(Params... p)
	{
		timesCalled++;
		return functionPointer(p...);
	}

	Return (*functionPointer)(Params...);
	int ID;
	int timesCalled;

private:
};


/// <summary>
/// Delegate action, containing the pointer to a function and other information
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template<class... Params>
class DDelegateAction<void, Params...>
{
public:
	DDelegateAction()
	{
        this->functionPointer = nullptr;
		ID = 0;
		timesCalled = 0;
	}
	DDelegateAction(int ID)
	{
        this->functionPointer = nullptr;
		this->ID = ID;
		timesCalled = 0;
	}
	DDelegateAction(void(*function)(Params...), int ID)
	{
		this->functionPointer = function;
		this->ID = ID;
		timesCalled = 0;
	}
	DDelegateAction(void(*function)(Params...))
	{
		this->functionPointer = function;
		this->ID = 0;
		timesCalled = 0;
	}
	~DDelegateAction()
	{

	}

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	void Fire(Params... p)
	{
		timesCalled++;
		functionPointer(p...);
	}

	void (*functionPointer)(Params...);
	int ID;
	int timesCalled;

private:
};