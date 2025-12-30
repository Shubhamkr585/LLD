#include <iostream>
#include <string>
#include <algorithm> 
using namespace std;

// ==========================================
// 1. The Target Interface
// Your App (Client) ONLY understands this interface.
// ==========================================
class IJsonAnalytics {
public:
    virtual void analyzeData(string jsonData) = 0;
    virtual ~IJsonAnalytics() {}
};

// ==========================================
// 2. The Adaptee (Legacy / 3rd Party)
// You cannot change this code. It speaks "XML".
// ==========================================
class LegacyStockLib {
public:
    string getStockDataXML() {
        return "<stock><symbol>GOOGL</symbol><price>2800</price></stock>";
    }
};

// ==========================================
// 3. The Adapter
// It looks like a JsonAnalytics tool on the outside,
// but works with the LegacyLib on the inside.
// ==========================================
class XmlAdapter : public IJsonAnalytics {
private:
    LegacyStockLib* legacyLib; // Composition: We "wrap" the legacy object

public:
    // Dependency Injection: Pass the legacy object in
    XmlAdapter(LegacyStockLib* lib) : legacyLib(lib) {}

    // The Translation Logic
    void analyzeData(string jsonData) override {
        // Step 1: Ignore the input 'jsonData' (or use it if needed)
        // Step 2: Get data from the Legacy Source
        string xmlData = legacyLib->getStockDataXML();
        
        // Step 3: Convert XML to JSON (Simulated logic)
        cout << "[Adapter] Converting XML: " << xmlData << endl;
        string convertedJson = "{ \"symbol\": \"GOOGL\", \"price\": 2800 }";
        cout << "[Adapter] Conversion Complete. Forwarding to Analytics Logic." << endl;

        // In a real app, you would pass 'convertedJson' to some internal processing logic
        cout << "✅ Analyzing JSON: " << convertedJson << endl;
    }
};

// ==========================================
// 4. The Client Code
// The client doesn't know XML exists. It just calls 'analyzeData'.
// ==========================================
int main() {
    // 1. Setup the Legacy System
    LegacyStockLib* oldSystem = new LegacyStockLib();

    // 2. Wrap it in the Adapter
    // Notice the type is 'IJsonAnalytics*' (The Target Interface)
    IJsonAnalytics* analyticsTool = new XmlAdapter(oldSystem);

    // 3. Use it!
    cout << "--- Client Application Started ---" << endl;
    analyticsTool->analyzeData(""); // The adapter handles the fetching internally here

    // Cleanup
    delete analyticsTool;
    delete oldSystem;

    return 0;
}