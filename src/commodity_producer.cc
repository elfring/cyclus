#include "commodity_producer.h"

#include "cyc_limits.h"
#include "error.h"

namespace cyclus {

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CommodInfo::CommodInfo()
  : capacity(0),
    cost(kModifierLimit) {}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CommodInfo::CommodInfo(double a_capacity,
                                           double a_cost)
  : capacity(a_capacity),
    cost(a_cost) {}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CommodityProducer::CommodityProducer()
  : default_capacity_(0.0),
    default_cost_(kModifierLimit) {}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CommodityProducer::~CommodityProducer() {}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::set<Commodity, CommodityCompare> CommodityProducer::ProducedCommodities() {
  std::set<Commodity, CommodityCompare> commodities;
  std::map<Commodity, CommodInfo, CommodityCompare>::iterator it;
  for (it = produced_commodities_.begin();
       it != produced_commodities_.end();
       it++) {
    commodities.insert(it->first);
  }
  return commodities;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool CommodityProducer::ProducesCommodity(const Commodity& commodity) {
  return (produced_commodities_.find(commodity) !=
          produced_commodities_.end());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double CommodityProducer::ProductionCapacity(const Commodity& commodity) {
  ThrowErrorIfCommodityNotProduced(commodity);
  return produced_commodities_[commodity].capacity;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double CommodityProducer::ProductionCost(const Commodity& commodity) {
  ThrowErrorIfCommodityNotProduced(commodity);
  return produced_commodities_[commodity].cost;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommodityProducer::AddCommodity(const Commodity& commodity) {
  CommodInfo info(default_capacity_, default_cost_);
  AddCommodityWithInformation(commodity, info);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommodityProducer::SetCapacity(const Commodity& commodity,
                                    double capacity) {
  ThrowErrorIfCommodityNotProduced(commodity);
  produced_commodities_[commodity].capacity = capacity;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommodityProducer::SetCost(const Commodity& commodity,
                                double cost) {
  ThrowErrorIfCommodityNotProduced(commodity);
  produced_commodities_[commodity].cost = cost;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommodityProducer::AddCommodityWithInformation(const Commodity& commodity,
                                                    const CommodInfo& info) {
  if (!ProducesCommodity(commodity)) {
    produced_commodities_.insert(std::make_pair(commodity, info));
  }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommodityProducer::CopyProducedCommoditiesFrom(CommodityProducer* source) {
  std::set<Commodity, CommodityCompare> commodities =
    source->ProducedCommodities();
  std::set<Commodity, CommodityCompare>::iterator it;
  for (it = commodities.begin(); it != commodities.end(); it++) {
    AddCommodity(*it);
    SetCapacity(*it, source->ProductionCapacity(*it));
    SetCost(*it, source->ProductionCost(*it));
  }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommodityProducer::ThrowErrorIfCommodityNotProduced(
  const Commodity& commodity) {
  if (!ProducesCommodity(commodity)) {
    throw KeyError("Producer does not produce "
                   + commodity.name());
  }
}
 
} // namespace cyclus
