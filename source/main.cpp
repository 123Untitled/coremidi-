#include "coremidi++/server.hpp"
#include "coremidi++/eventlist.hpp"

int main(void) {


	coremidi::eventlist evlst;
	coremidi::client client{"msh midi client"};
	coremidi::endpoint source{coremidi::make_source(client, "msh")};

	coremidi::u8 note = 60U;

	while (true) {
		std::cout << "num packets: " << evlst.num_packets() << std::endl;
		std::cout << "word count: " << evlst.word_count() << std::endl;
		std::cout << "size: " << evlst.size() << std::endl;


		evlst.note_on(0U, note, 127U);
		evlst.send(source);

		usleep(100000);

		evlst.note_off(0U, note);
		evlst.send(source);

		usleep(100000);

		std::cout << "note: " << (int)note << std::endl;

		note = (note > 110) ? 50 : note + 1;
	}

	return 0;
}
