#pragma once
#include "SoundSystem.h"
namespace dae
{
	class servicelocator final
	{
		static SoundSystem* m_pSoundSystem;
		static null_sound_system m_pDefaultSystem;
	public:
		static SoundSystem& get_sound_system() { return *m_pSoundSystem; }
		static void register_sound_system(SoundSystem* ss) { m_pSoundSystem = ss == nullptr ? &m_pDefaultSystem : ss; }
		static void destroy_sound_system()
		{
			m_pSoundSystem->Cleanup();
			delete m_pSoundSystem;
			m_pSoundSystem = nullptr;
		}
	};

}

