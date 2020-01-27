#pragma once
#include "Gui.h"

namespace graphics
{
	void change_cursor_position(int x, int y);
	void change_cursor_position(COORD position);

	class Console : public Gui
	{
	public:
		Console(int width, int height);
		virtual ~Console();
		void get_cursor_position();
		virtual void get_events() override;
		virtual void draw() override;
	private:
		class outbuf : public std::streambuf {
		public:
			outbuf() {
				setp(0, 0);
			}

			virtual int_type overflow(int_type c = traits_type::eof()) {
				return fputc(c, stdout) == EOF ? traits_type::eof() : c;
			}
		};
		outbuf ob;
		std::streambuf *sb = nullptr;
		HANDLE stdin_handle;
		DWORD fdwMode, fdwSaveOldMode;
	};
}
