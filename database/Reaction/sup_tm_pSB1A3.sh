file = [sup_tm_pSB1A3.xml]

MoDeL
{
	reaction id = [sup_tm_pSB1A3], name = [suppression of tm_pSB1A3], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[suppression of plasmid template pSB1A3];
		}
		listOfCompartments
		{
			compartment
			{
				compartmentReference:[Flask];
				currentCompartmentLabel:[Flask];
				parentCompartmentLabel:[ROOT];
			}
			compartment
			{
				compartmentReference:[E_coli];
				currentCompartmentLabel:[E_coli];
				parentCompartmentLabel:[Flask];
			}
		}
		listOfReactants
		{
			reactant
			{
				speciesReference:[tm_pSB1A3];
				speciesLabel:[tm_pSB1A3_0];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfModifiers
		{
			modifier
			{
				speciesReference:[tm_pSB1A3];
				speciesLabel:[tm_pSB1A3_1];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfProducts
		{
		}
		listOfSubstituentTransfers
		{
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math:[ksup*(tm_pSB1A3_0/copynum)*tm_pSB1A3_1*E_coli];
				listOfLocalParameters
				{
					localParameter
					{
						id:[ksup];
						name:[rate of suppression];
						value:[0.1];
						units:[per_second];
						constant:[true];
					}
				}
				listOfReferencedParameters
				{
					referencedParameter
					{
						id:[copynum];
						extRefSource:[copyNumber] speciesLabel = [tm_pSB1A3_0], partLabel = [pSB1A3];
					}
				}
				listOfConstraints
				{
				}
			}
			reverseKineticLaw
			{
			}
		}
	}
}
