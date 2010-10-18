// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/utilities/CSlider.h,v $
//   $Revision: 1.15 $
//   $Name: Build-31 $
//   $Author: ssahle $
//   $Date: 2009/04/24 12:52:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CSlider
#define COPASI_CSlider

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

class CSlider : public CCopasiContainer
{
public:
  /**
   *  Enum of valid quantitye units
   */
  enum Type {Float = 0, UnsignedFloat, Integer, UnsignedInteger, Undefined};

  /**
   *  Enum of valid scales
   */
  enum Scale {linear = 0, logarithmic, undefinedScale};

  /**
   * String representation of valid quantity units
   */
  static const char * TypeName[];

  /**
   * String representation of valid scalings
   */
  static const char * ScaleName[];

  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CSlider(const std::string & name = "Slider",
          const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CSlider & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CSlider(const CSlider & src,
          const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CSlider();

  /**
   * Compile, i.e., find the objects pointed to by the CN.
   * @param const std::vector< CCopasiContainer * > & listOfContainer
   *  (default: CCopasiContainer::EmptyList)
   * @return bool success
   */
  bool compile(const std::vector< CCopasiContainer * > & listOfContainer = CCopasiContainer::EmptyList);

  /**
   * Retrieve the key
   * @return const std::string & key
   */
  const std::string & getKey() const;

  /**
   * Set the key of the associated entity
   * @param const std::string & associatedEntityKey
   * @return bool succes
   */
  bool setAssociatedEntityKey(const std::string & associatedEntityKey);

  /**
   * Retrieve the key of the associated entity.
   * @return const std::string & associatedEntityKey
   */
  const std::string & getAssociatedEntityKey() const;

  /**
   * Set the slider object.
   * @param CCopasiObject * pObject
   * @return bool succes
   */
  bool setSliderObject(CCopasiObject * pObject);

  /**
   * Set the slider object.
   * @param const CCopasiObjectName & objectCN
   * @return bool succes
   */
  bool setSliderObject(const CCopasiObjectName & objectCN);

  /**
   * Retrieve the slider object.
   * @return CCopasiObject * pObject
   */
  CCopasiObject * getSliderObject();

  /**
   * Retrieve the slider object CN.
   * @return const std::string & sliderObjectCN
   */
  const std::string & getSliderObjectCN() const;

  /**
   * Set the slider type.
   * @param const CSlider::Type  type
   * @return bool succes
   */
  bool setSliderType(const CSlider::Type type);

  /**
   * Retrieve the slider type.
   * @return const CSlider::Type  type
   */
  CSlider::Type getSliderType() const;

  /**
   * Set the sliders original value.
   * @param const C_FLOAT64 Value
   * @param const bool & writeToObject (Default: true)
   * @return bool succes
   */
  bool setOriginalValue(const C_FLOAT64 value);

  /**
   * Retrieve the original slider Value.
   * @return const C_FLOAT64 Value
   */
  const C_FLOAT64 & getOriginalValue() const;

  /**
   * Set the slider value.
   * @param const C_FLOAT64 Value
   * @param const bool & writeToObject (Default: true)
   * @return bool succes
   */
  bool setSliderValue(const C_FLOAT64 value,
                      const bool & writeToObject = true);

  /**
   * Sets the value of the slider back to it's original
   * value.
   */
  void resetValue();

  /**
   * Retrieve the slider Value.
   * @return const C_FLOAT64 Value
   */
  const C_FLOAT64 & getSliderValue() const;

  /**
   * Set the slider minimum value.
   * @param const C_FLOAT64 minValue
   * @return bool succes
   */
  bool setMinValue(const C_FLOAT64 minValue);

  /**
   * Retrieve the slider minimum value.
   * @return const C_FLOAT64  minValue
   */
  const C_FLOAT64 & getMinValue() const;

  /**
   * Set the slider maximum value.
   * @param const C_FLOAT64 maxValue
   * @return bool succes
   */
  bool setMaxValue(const C_FLOAT64 maxValue);

  /**
   * Retrieve the slider maximum value.
   * @return const C_FLOAT64 & maxValue
   */
  const C_FLOAT64 & getMaxValue() const;

  /**
   * Set the tick number.
   * @param const unsigned C_INT32 & tickNumber
   * @return bool succes
   */
  bool setTickNumber(const unsigned C_INT32 tickNumber);

  /**
   * Retrieve the tick number.
   * @return const unsigned C_INT32 & tickNumber
   */
  unsigned C_INT32 getTickNumber() const;

  /**
   * Set the tick factor.
   * @param const unsigned C_INT32 & tickFactor
   * @return bool succes
   */
  bool setTickFactor(const unsigned C_INT32 tickFactor);

  /**
   * Retrieve the tick factor.
   * @return const unsigned C_INT32 & tickFactor
   */
  unsigned C_INT32 getTickFactor() const;

  /**
   * Set the scaling for the CSlider.
   */
  bool setScaling(Scale scaling);

  /**
   * Retrieve the scaling of the slider.
   * @return Scale scaling
   */
  Scale getScaling() const;

  /**
   * Reset the minimum and maximum value to defaults. For the minimum this is
   * half the current value. For the maximum this is twice the current value.
   */
  void resetRange();

  /**
   * Sets wether the value is to be kept in sync the the objects value.
   */
  void setSynced(bool synced);

  /**
   * Returns wether the value is to be kept in sync the the objects value.
   * @return bool isSynced.
   */
  bool getSynced() const;

  /**
   * Set the CSliders value to the value of the underlying object.
   */
  void sync();

  /**
   * Set the objects value to the value stored in CSlider.
   */
  void writeToObject();

  /**
   * Converts the scaling name to the corresponding enum.
   * @return CSlider::Scale
   */
  Scale convertScaleNameToScale(const char* scaleName);

  /**
   * Converts the scaling name to the corresponding enum.
   * @return const char* scaleName
   */
  const char* convertScaleToScaleName(Scale scale);

  // Attributes
private:
  /**
   * The key of the slider.
   */
  std::string mKey;

  /**
   * The key of the associated entity of the slider's object.
   */
  std::string mAssociatedEntityKey;

  /**
   * The slider object pointing to the slider's object afteer compile.
   */
  CCopasiObject * mpSliderObject;

  /**
   * The value type of the slider's object.
   */
  Type mSliderType;

  /**
   * The value of the slider-
   */
  C_FLOAT64 mValue;

  /**
   * The original value of the slider-
   */
  C_FLOAT64 mOriginalValue;

  /**
   * The minimun value of the slider
   */
  C_FLOAT64 mMinValue;

  /**
   * The maximum value of the slider
   */
  C_FLOAT64 mMaxValue;

  /**
   * The number of ticks the slider is divided into.
   */
  unsigned C_INT32 mTickNumber;

  /**
   * The factor between minor and major ticks.
   */
  unsigned C_INT32 mTickFactor;

  /**
   * Wether the CSlider's value is always in sync with its object's value.
   */
  bool mSync;

  /**
   * The scaling of the slider.
   */
  Scale mScaling;

  /**
   * The CN of the object that the slider modifies.
   */
  CRegisteredObjectName mCN;

  /**
   * The sequnece of methods to update initial values depending on this sliders
   * object.
   */
  std::vector< Refresh * > mInitialRefreshes;
};

#endif
