#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Abstract Class
class ProductionLine {
protected:
    string lineID;
    int unitsProduced;
    int unitsDefective;

public:
    static int activeAssemblyLines;
    static int totalFactoryUnitsProduced;

    ProductionLine(string id, int produced, int defective)
        : lineID(id), unitsProduced(produced), unitsDefective(defective) {
        activeAssemblyLines++;
        totalFactoryUnitsProduced += produced;
    }

    virtual ~ProductionLine() {
        cout << "[SHUTDOWN] Assembly Line " << lineID << " offline. Power cut." << endl;
        activeAssemblyLines--;
    }

    // Pure Virtual Functions
    virtual double calculateYieldPercentage() const = 0;
    virtual void printProductionAudit() const = 0;
};

// Static variables initialized outside class boundary
int ProductionLine::activeAssemblyLines = 0;
int ProductionLine::totalFactoryUnitsProduced = 0;

// Derived Class 1: Automated Robotic Assembly Line
class RoboticAssemblyLine : public ProductionLine {
private:
    int operationalRobots;
    double energyConsumedKWh;

public:
    RoboticAssemblyLine(string id, int produced, int defective, int robots, double energy)
        : ProductionLine(id, produced, defective),
          operationalRobots(robots),
          energyConsumedKWh(energy) {}

    ~RoboticAssemblyLine() override {
        cout << " -> Locking robotic arms and calibrating servomotors for " << lineID << "..." << endl;
    }

    double calculateYieldPercentage() const override {
        if (unitsProduced == 0) return 0.0;
        int usable = unitsProduced - unitsDefective;
        return (static_cast<double>(usable) / unitsProduced) * 100.0;
    }

    void printProductionAudit() const override {
        cout << "\n==============================================" << endl;
        cout << "   ROBOTIC ASSEMBLY LINE AUDIT: " << lineID << endl;
        cout << "==============================================" << endl;
        cout << "  Active Robotic Units : " << operationalRobots << endl;
        cout << "  Total Units Molded   : " << unitsProduced << endl;
        cout << "  Defective Rejections : " << unitsDefective << endl;
        cout << "  Operational Yield    : " << fixed << setprecision(2) 
             << calculateYieldPercentage() << "%" << endl;
        cout << "  Grid Power Consumed  : " << energyConsumedKWh << " kWh" << endl;
        cout << "  Status               : " 
             << (calculateYieldPercentage() >= 95.0 ? "OPTIMAL" : "MAINTENANCE REQUIRED") << endl;
        cout << "==============================================" << endl;
    }
};

// Derived Class 2: Manual Quality Control / Packaging Line
class ManualPackagingLine : public ProductionLine {
private:
    int workerShiftCount;
    string supervisorName;

public:
    ManualPackagingLine(string id, int produced, int defective, int workers, string supervisor)
        : ProductionLine(id, produced, defective),
          workerShiftCount(workers),
          supervisorName(supervisor) {}

    ~ManualPackagingLine() override {
        cout << " -> Archiving shift logs and dispatching conveyor belts for " << lineID << "..." << endl;
    }

    double calculateYieldPercentage() const override {
        if (unitsProduced == 0) return 0.0;
        int usable = unitsProduced - unitsDefective;
        return (static_cast<double>(usable) / unitsProduced) * 100.0;
    }

    void printProductionAudit() const override {
        cout << "\n==============================================" << endl;
        cout << "   PACKAGING & DISPATCH LINE AUDIT: " << lineID << endl;
        cout << "==============================================" << endl;
        cout << "  Floor Supervisor     : " << supervisorName << endl;
        cout << "  Staff on Shift       : " << workerShiftCount << " technicians" << endl;
        cout << "  Total Packaged Units : " << unitsProduced << endl;
        cout << "  Damaged Packages     : " << unitsDefective << endl;
        cout << "  Final Yield Rate     : " << fixed << setprecision(2) 
             << calculateYieldPercentage() << "%" << endl;
        cout << "  Status               : " 
             << (calculateYieldPercentage() >= 90.0 ? "DISPATCH READY" : "INSPECTION FLAGGED") << endl;
        cout << "==============================================" << endl;
    }
};

int main() {
    cout << "\n>>> STARTING FACTORY CENTRAL TELEMETRY <<<\n" << endl;

    const int TOTAL_LINES = 2;
    ProductionLine* plantFloor[TOTAL_LINES];

    // Heap allocation for different factory lines
    // Line 1: Robotic assembly (1200 produced, 18 defective, 8 robots, 450.5 kWh)
    plantFloor[0] = new RoboticAssemblyLine("ROBO-LINE-A", 1200, 18, 8, 450.5);

    // Line 2: Manual packaging (600 produced, 45 defective, 15 workers, Supervisor "Ahmed Raza")
    plantFloor[1] = new ManualPackagingLine("PACK-LINE-B", 600, 45, 15, "Ahmed Raza");

    // Dynamic polymorphic dispatch
    for (int i = 0; i < TOTAL_LINES; i++) {
        plantFloor[i]->printProductionAudit();
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Operational Lines   : " << ProductionLine::activeAssemblyLines << endl;
    cout << "Total Plant Output Batches : " << ProductionLine::totalFactoryUnitsProduced << " units" << endl;
    cout << "----------------------------------------------\n" << endl;

    cout << ">>> INITIATING END-OF-SHIFT TEARDOWN <<<\n" << endl;

    // Polymorphic destruction & cleanup
    for (int i = 0; i < TOTAL_LINES; i++) {
        delete plantFloor[i];
        plantFloor[i] = nullptr;
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Operational Lines After Teardown: " << ProductionLine::activeAssemblyLines << endl;
    cout << "----------------------------------------------" << endl;

    return 0;
}
