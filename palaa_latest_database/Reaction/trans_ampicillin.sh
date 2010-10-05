file = [trans_ampicillin.xml]

MoDeL
{
	reaction id = [trans_ampicillin], name = [transport ampicillin], reversible = [true], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[transport of ampicillin inward and outward E_coli];
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
				speciesReference:[ampicillin_compound];
				speciesLabel:[ampicillin_compound_in];
				compartmentLabel:[E_coli];
			}
		}
		listOfModifiers
		{
		}
		listOfProducts
		{
			product
			{
				speciesReference:[ampicillin_compound];
				speciesLabel:[ampicillin_compound_out];
				compartmentLabel:[E_coli];
			}
		}
		listOfSubstituentTransfers
		{
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math:[kon*ampicillin_compound_in*E_coli];
				listOfLocalParameters
				{
					localParameter
					{
						id:[kon];
						name:[rate of outward transport];
						value:[1E-14];
						units:[per_second];
						constant:[true];
					}
				}
				listOfReferencedParameters
				{
				}
				listOfConstraints
				{
				}
			}
			reverseKineticLaw
			{
				math:[koff*ampicillin_compound_out*Flask];
				listOfLocalParameters
				{
					localParameter
					{
						id:[koff];
						name:[rate of inward transport];
						value:[0.25];
						units:[per_second];
						constant:[true];
					}
				}
				listOfReferencedParameters
				{
				}
				listOfConstraints
				{
				}
			}
		}
	}
}
