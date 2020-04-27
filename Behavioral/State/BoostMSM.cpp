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
	bool angry{ true };

	struct OffHook : boost::msm::front::state<> {};
	struct Connecting : boost::msm::front::state<> 
	{
		template<typename Event, typename FSM>
		void on_entry(Event const& evt, FSM&)
		{
			std::cout << "We are connecting... " << std::endl;
		}
	};

	struct PhoneBeingDestroyed
	{
		template<typename EVT, typename FSM, typename SourceState, typename TargetState>
		void operator()(EVT const&, FSM const&, SourceState&, TargetState&)
		{
			std::cout << "Phone breaks into a million pieces" << std::endl;
		}
	};

	struct CanDestroyPhone
	{
		template<typename EVT, typename FSM, typename SourceState, typename TargetState>
		bool operator()(EVT const&, FSM const& fsm, SourceState&, TargetState&)
		{
			return fsm.angry;
		}
	};

	struct Connected : boost::msm::front::state<> {};
	struct OnHold : boost::msm::front::state<> {};
	struct PhoneDestroyed : boost::msm::front::state<> {};

	struct transition_table : boost::mpl::vector<
		boost::msm::front::Row<OffHook, CallDialed, Connecting>,
		boost::msm::front::Row<Connecting, CallConnected, Connected>,
		boost::msm::front::Row<Connected, PlacedOnHold, OnHold>,
		boost::msm::front::Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
	> {};

	typedef OffHook initial_state;

	template<typename FSM, typename Event>
	void no_transition(Event const& e, FSM&, int state)
	{
		std::cout << "No transition from state " << state_names[state]
			<< " on event " << typeid(e).name() << std::endl;
	}
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
	phone.process_event(CallConnected{});
	info();
	phone.process_event(PlacedOnHold{});
	info();
	phone.process_event(PhoneThrownIntoWall{});
	info();
	phone.process_event(CallDialed{});

	return 0;
}