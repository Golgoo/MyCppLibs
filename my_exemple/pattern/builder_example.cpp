#include <my/pattern/factory.hpp>
#include <my/pattern/builder.hpp>

#include <iostream>

int counter = 0 ;
//The class that should be build by a builder
class ClassToBuild{
    
    private :
        int _instance_num ;
    public:
        ClassToBuild()
        {
            _instance_num = ++counter ;
            std::cout << "Class to build num : " << _instance_num << " -> created" << std::endl;
        }
        ~ClassToBuild()
        {
            std::cout << "Class to build num : " << _instance_num << " -> destroyed" << std::endl;
        }

    public:
        int single_value ;
        double double_value ;
};

//The way builder instanciate the object to build
class ClassToBuildFactory : public my::pattern::Factory<ClassToBuild>
{
    public:
        ClassToBuild * create() override {
            ClassToBuild * instance = new ClassToBuild();
            return instance ;
        }
};
ClassToBuildFactory factory ;

//Some enum only for example
enum BuilderOperation{
    SINGLE_VALUE,
    DOUBLE_VALUE,
};

//The builder extension
class ClassToBuildBuilder : public my::pattern::Builder<ClassToBuild>
{
    public:
        ClassToBuildBuilder(my::pattern::Factory<ClassToBuild>& factory)
        : Builder(&factory)
        {
            init_operations();
        }
    private:
        //Init the builder's operations OR you can init them rawly
        void init_operations(){
            registerBuildingOperation(BuilderOperation::SINGLE_VALUE, [](ClassToBuild &classToBuild){
                classToBuild.single_value = 5 ;
            });
            registerBuildingOperation(BuilderOperation::DOUBLE_VALUE, [](ClassToBuild &ClassToBuild){
                ClassToBuild.double_value = 8.2 ;
            });
        }
};



int main(void)
{
    std::cout << "Creating the first instance with the builder" << std::endl ;
    std::unique_ptr<my::pattern::Builder<ClassToBuild>> builder (new ClassToBuildBuilder(factory));
    //Init the builder's operations OR you can init them in the Builder's extension
    {
        builder->registerBuildingOperation(BuilderOperation::SINGLE_VALUE, [](ClassToBuild &classToBuild){
            classToBuild.single_value = 5 ;
        });
        builder->registerBuildingOperation(BuilderOperation::DOUBLE_VALUE, [](ClassToBuild &ClassToBuild){
            ClassToBuild.double_value = 8.2 ;
        });
    }
    
    builder->processOperation(BuilderOperation::SINGLE_VALUE);
    builder->processOperation(BuilderOperation::DOUBLE_VALUE);
    {
        std::cout << "Asking the built instance (1)" << std::endl;
        std::shared_ptr<ClassToBuild> builtClass1 = builder->buildIt();
        std::cout << "Another instance is ready to be built (2)" << std::endl;
        std::cout << "..." << std::endl;
        std::cout << "No more need of this instance (1)" << std::endl;
    }
    builder->processOperation(BuilderOperation::SINGLE_VALUE);
    {
        std::cout << "Asking another built instance (2)" << std::endl;
        std::shared_ptr<ClassToBuild> builtClass1 = builder->buildIt();
        std::cout << "Another instance is ready to be built(3)" << std::endl;
        std::cout << "..." << std::endl;
        std::cout << "No more need of this instance (2)" << std::endl;
    }
    std::cout << "No more need of the builder " << std::endl;
}