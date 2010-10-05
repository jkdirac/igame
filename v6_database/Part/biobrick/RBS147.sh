file = [RBS147.xml]

MoDeL
{
	part
	{
		biobrick id = [RBS147], name = [RBS.1 (BBa_B0030)], originalConformation = []
		{
			interface
			{
				url:[http://partsregistry.org/cgi/xml/part.cgi?part=BBa_B0030];
				shortDesc:[RBS.1 (strong) __ modified from R. Weiss]; 
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [forwardRbsEfficiency], name = [efficiency as a RBS when translated forward], commonValue = [], units = [per_second]
				{
					parameterValue:[6.93] compartment = [E_coli];
				}
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[placI185_dna] partType = [ForwardDNA];
			}
		}
	}
}



