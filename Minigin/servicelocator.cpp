#include "servicelocator.h"
dae::null_sound_system dae::servicelocator::m_pDefaultSystem{};
dae::SoundSystem* dae::servicelocator::m_pSoundSystem = &m_pDefaultSystem;