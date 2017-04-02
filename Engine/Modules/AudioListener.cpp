void AudioListener::Update()
{
    Audio::ChangeListenerPosition(entity->transform.GetPosition());
    Audio::ChangeListenerOrientation(entity->transform.Forward(), entity->transform.Up());
}