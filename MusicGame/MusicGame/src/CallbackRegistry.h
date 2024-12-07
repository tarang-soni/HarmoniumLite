#pragma once
template<typename T>
class CallbackRegistry {
private:
    // Static map of function names to member function pointers
    static inline std::unordered_map<std::string, void (T::*)()> callbackMap;

public:
    // Registration method to be called during initialization
    template<auto Callback>
    static void RegisterCallback(const std::string& name) {
        callbackMap[name] = Callback;
    }

    // Get callback for a specific object
    static std::function<void()> GetCallback(T& obj, const std::string& functionName) {
        auto it = callbackMap.find(functionName);
        if (it != callbackMap.end()) {
            return std::bind(it->second, &obj);
        }
        return {};
    }
};