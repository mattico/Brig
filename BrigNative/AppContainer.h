#pragma once

ref class AppContainer
{
public:
    AppContainer(String^ executablePath);

    void Run();

    property String^ ExecutablePath {
        String^ get() { return m_ExecutablePath; }
    }
    property String^ Name;
    property String^ DisplayName;
    property String^ Description;
    property String^ StringSid {
        String^ get() { return m_StringSid; }
    }

private:
    String ^m_ExecutablePath;
    String ^m_StringSid;
};

