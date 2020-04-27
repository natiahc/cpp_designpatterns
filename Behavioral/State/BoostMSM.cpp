#include <iostream>
#include <string>
#include <vector>

//backend
#include <boost/msm/back/state_machine.hpp>

//frontend
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

std::vector<std::string> state_names{
	"off hook",
	"connecting",
	"connected",
	"on hold",
	"destroyed"
};

struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : boost::msm::front::state_machine_def<PhoneStateMachine>
{
	struct OffHook : boost::msm::front::state<> {};
	struct Connecting : boost::msm::front::state<> {};
	struct Connected : boost::msm::front::state<> {};
	struct OnHold : boost::msm::front::state<> {};
	struct PhoneDestroyed : boost::msm::front::state<> {};

	struct transition_table : boost::mpl::vector<
		boost::msm::front::Row<OffHook, CallDialed, Connecting>,
		boost::msm::front::Row<Connecting, CallConnected, Connected>,
		boost::msm::front::Row<Connected, PlacedOnHold, OnHold>,
		boost::msm::front::Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed>
	> {};

	typedef OffHook initial_state;
};

int main()
{
	boost::msm::back::state_machine<PhoneStateMachine> phone;
	auto info = [&]()
	{
		auto i = phone.current_state()[0];
		std::cout << "The phone is currently " << state_names[i] << std::endl;
	};

	info();
	phone.process_event(CallDialed{});
	info();

	return 0;
}