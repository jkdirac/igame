file = [tm_dil_ecoli.xml]

MoDeL
{
	reaction id = [tm_dil_ecoli.xml], name = [template dilution in E_coli], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[template of dilution reaction in E_coli];
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
				speciesReference:[any_species];
				speciesLabel:[any_species];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfModifiers
		{
			modifiers
			{
				speciesReference:[E_coli_cell];
				speciesLabel:[E_coli_cell];
				compartmentLabel:[Flask] itself = [E_coli];
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
				math:[kgrowth*(1-(E_coli_cell/macx))*any_species*E_coli];
				listOfLocalParameters
				{
				}
				listOfReferencedParameters
				{
					referencedParameter
					{
						id:[kgrowth];
						extRefSource:[growthRate] speciesLabel = [E_coli_cell], partLabel = [E_coli];
					}
					referencedParameter
					{
						id:[maxc];
						extRefSource:[maxConcentration] speciesLabel = [E_coli_cell], partLabel = [E_coli];
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
